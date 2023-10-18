/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:38:09 by fbohling          #+#    #+#             */
/*   Updated: 2023/10/18 12:53:26 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo(t_data *data)
{
	init_philos(data);
	init_forks(data);
	init_threads(data);
}

void	*routine(void *philo)
{
	t_philo		*p;

	p = (t_philo *)philo;
	while (1)
	{
		display_action(THINK, p);
		pthread_mutex_lock(&p->data->death);
		if (p->data->dead)
		{
			pthread_mutex_unlock(&p->data->death);
			return (NULL);
		}
		pthread_mutex_unlock(&p->data->death);
		actions(p);
	}
	return (NULL);
}

void	*supervisor(void *data)
{
	t_data			*d;
	int				i;

	d = (t_data *)data;
	while (1)
	{
		i = -1;
		while (++i < d->philo_n)
		{
			pthread_mutex_lock(&d->death);
			if (!d->philos[i].eat_stat && (get_time() >= d->philos[i].time_to_die))
			{
				// pthread_mutex_lock(&d->printmutex);
				// printf("%llu, %d\n", d->philos[i].time_to_die - d->philos[i].birth_time, d->philos[i].id);
				// pthread_mutex_unlock(&d->printmutex);
				d->dead = 1;
				pthread_mutex_unlock(&d->death);
				display_action(DEAD, &d->philos[i]);
				return (NULL);
			}
			pthread_mutex_unlock(&d->death);
		}
	}
	return (NULL);
}

void	end_sim(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->philo_n)
	{
		if (pthread_join(d->tid[i], NULL))
			return (clean(d));
		i++;
	}
	return ;
}
