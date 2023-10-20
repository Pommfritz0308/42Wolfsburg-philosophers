/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:50:17 by fbohling          #+#    #+#             */
/*   Updated: 2023/10/20 12:13:48 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	format_input(char **argv, t_data *data)
{
	int		count;
	char	**array;
	char	*str;
	char	*temp;

	count = 1;
	str = ft_strdup(argv[1]);
	while (argv[++count])
	{
		temp = ft_strjoin(str, " ");
		free(str);
		str = ft_strjoin(temp, argv[count]);
		free(temp);
	}
	array = format_input_helper(data, str);
	count = -1;
	while (array[++count])
	{
		data->arr[count] = ft_atoi_philo(array[count]);
		if (data->arr[count] == -1)
			return (ft_free_array(array), free(str), false);
	}
	ft_free_array(array);
	return (free(str), true);
}

bool	handle_input(char *argv[])
{
	int		i;
	int		j;
	char	**arr;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		arr = ft_split(argv[i], ' ');
		while (arr[++j])
		{
			if (!check_digits(arr[j]))
			{
				ft_free_array(arr);
				printf("\033[1;31mONLY POSITIVE NUMERIC ARGUMENTS!\033[0m\n");
				return (false);
			}
		}
		ft_free_array(arr);
	}
	return (true);
}

bool	check_digits(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '-')
			return (false);
		else if (s[i] == '+')
			i++;
		if ('0' <= s[i] && s[i] <= '9')
			i++;
		else
			return (false);
	}
	return (true);
}

bool	conversion(const char *str, int *result, int *sign)
{
	int	digit;

	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		if (*sign == 1 && (*result > INT_MAX / 10
				|| (*result == INT_MAX / 10 && digit > INT_MAX % 10)))
		{
			printf("\033[1;31mEXCEEDING MAX INT\033[0m\n");
			return (false);
		}
		else if (*sign == -1 && (*result > -(INT_MIN / 10)
				|| (*result == -(INT_MIN / 10) && digit > -(INT_MIN % 10))))
		{
			printf("\033[1;31mEXCEEDING MIN INT\033[0m\n");
			return (false);
		}
		*result = *result * 10 + digit;
		str++;
	}
	return (true);
}

char	**format_input_helper(t_data *data, char *str)
{
	char	**array;

	array = ft_split(str, ' ');
	data->size = 0;
	while (array[data->size])
		data->size++;
	data->arr = malloc(data->size * sizeof(int));
	return (array);
}
