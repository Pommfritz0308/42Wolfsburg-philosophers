/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:40:23 by fbohling          #+#    #+#             */
/*   Updated: 2023/10/20 11:40:36 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_death(void *data)
{
	t_data			*d;
	int				i;

	d = (t_data *)data;
	while (1)
	{
		i = -1;
		while (++i < d->philo_n)
		{
			pthread_mutex_lock(&d->monitor);
			if (check_death_helper(d, i))
				return (NULL);
			pthread_mutex_unlock(&d->monitor);
		}
	}
	return (NULL);
}

int	check_death_helper(t_data *d, int i)
{
	if (d->finished)
	{
		pthread_mutex_unlock(&d->monitor);
		return (1);
	}
	if (!d->philos[i].eat_stat
		&& (get_time() >= d->philos[i].time_to_die))
	{
		d->finished = 1;
		pthread_mutex_unlock(&d->monitor);
		display_action(DEAD, &d->philos[i]);
		if (d->philo_n == 1)
			pthread_mutex_unlock(d->philos[i].right);
		return (1);
	}
	return (0);
}

void	*check_finished(void *data)
{
	t_data	*d;
	int		i;

	d = (t_data *)data;
	while (1)
	{
		pthread_mutex_lock(&d->monitor);
		if (!d->meal_n || d->finished_philos == d->philo_n || d->finished)
		{
			d->finished = 1;
			pthread_mutex_unlock(&d->monitor);
			return (NULL);
		}
		pthread_mutex_unlock(&d->monitor);
		i = -1;
		while (++i < d->philo_n)
			check_finished_helper(d, i);
	}
	return (NULL);
}

void	check_finished_helper(t_data *d, int i)
{
	pthread_mutex_lock(&d->monitor);
	if (d->philos[i].eat_n == d->meal_n)
	{
		if (d->philos[i].status == 0)
			d->finished_philos++;
		d->philos[i].status = 1;
	}
	pthread_mutex_unlock(&d->monitor);
}

void	destroy_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_n)
		pthread_mutex_destroy(&(data->forks[i]));
	free(data->forks);
}
