/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:38:09 by fbohling          #+#    #+#             */
/*   Updated: 2023/10/20 17:13:41 by fbohling         ###   ########.fr       */
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
	if (p->id % 2 == 0)
		ft_usleep(p->data->eating_time / 2);
	while (1)
	{
		pthread_mutex_lock(&p->data->monitor);
		if (p->data->finished || p->status)
		{
			pthread_mutex_unlock(&p->data->monitor);
			return (NULL);
		}
		pthread_mutex_unlock(&p->data->monitor);
		actions(p);
		display_action(THINK, p);
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
