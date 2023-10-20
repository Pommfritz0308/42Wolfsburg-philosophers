/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 18:36:57 by fbohling          #+#    #+#             */
/*   Updated: 2023/10/20 15:45:09 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data)
{
	int	i;

	i = 0;
	data->philo_n = data->arr[0];
	data->death_time = data->arr[1];
	data->eating_time = data->arr[2];
	data->sleep_time = data->arr[3];
	data->finished_philos = 0;
	data->finished = 0;
	data->dead = 0;
	if (data->size == 5)
		data->meal_n = data->arr[4];
	pthread_mutex_init(&data->printmutex, NULL);
	pthread_mutex_init(&data->monitor, NULL);
	free(data->arr);
}

void	init_philos(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->philo_n)
	{
		d->philos[i].id = i + 1;
		d->philos[i].data = d;
		d->philos[i].eat_n = 0;
		d->philos[i].eat_stat = 0;
		d->philos[i].status = 0;
		i++;
	}
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
		printf("PHILO[%i]: LEFT FORK: %p, RIGHT FORK: %p\n", data->philos[i].id, data->philos[i].left, data->philos[i].right);
		i++;
	}
}

void	clean(t_data *data)
{
	if (data->tid)
		free(data->tid);
	if (data->philos)
		free(data->philos);
	destroy_forks(data);
}
