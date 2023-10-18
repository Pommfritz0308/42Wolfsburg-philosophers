/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:50:17 by fbohling          #+#    #+#             */
/*   Updated: 2023/10/18 18:51:26 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	format_input(char **argv, t_data *data)
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
	array = ft_split(str, ' ');
	data->size = 0;
	while (array[data->size])
		data->size++;
	data->arr = malloc(data->size * sizeof(int));
	count = -1;
	while (array[++count])
		data->arr[count] = ft_atoi_philo(array[count]);
	ft_free_array(array);
	return (free (str));
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
				printf("\033[1;31mONLY POSITIVE NUMERIC ARGUMENTS!\031\n");
				exit (1);
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
