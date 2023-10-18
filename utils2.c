/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:43:13 by fbohling          #+#    #+#             */
/*   Updated: 2023/10/17 14:13:54 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

uint64_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(uint64_t duration)
{
	uint64_t	start;

	start = get_time();
	while (get_time() - start < duration)
	{
	}
	return ;
}

void	init_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_n)
		pthread_mutex_init(&(data->forks[i]), NULL);
	i = 0;
	while (i < data->philo_n)
	{
		data->philos[i].left = &(data->forks[i]);
		data->philos[i].right = &(data->forks[(i + 1) % data->philo_n]);
		i++;
	}
	// i = 0;
	// while (i < data->philo_n)
	// {
	// 	printf("PHILO[%i]| left fork: %p, right fork: %p\n",
	// 		i, (void*)(data->philos[i].left), (void*)(data->philos[i].right));
	// 	i++;
	// }
}

void	display_action(char *action, t_philo *p)
{
	pthread_mutex_lock(&p->data->death);
	if (!p->data->dead || !ft_strncmp(action, DEAD, ft_strlen(DEAD)))
	{
		pthread_mutex_lock(&p->data->printmutex);
		printf("%llu %i", get_time() - p->birth_time, p->id);
		printf("%s", action);
		pthread_mutex_unlock(&p->data->printmutex);
	}
	pthread_mutex_unlock(&p->data->death);
}
