/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:43:13 by fbohling          #+#    #+#             */
/*   Updated: 2023/10/18 18:51:20 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	alloc_struct(t_data *data)
{
	data->tid = (pthread_t *)malloc(sizeof(pthread_t) * data->philo_n);
	if (!data->tid)
		return (false);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->philo_n);
	if (!data->forks)
		return (false);
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->philo_n);
	if (!data->philos)
		return (false);
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

void	display_action(char *action, t_philo *p)
{
	pthread_mutex_lock(&p->data->monitor);
	if (!p->data->finished || !ft_strncmp(action, DEAD, ft_strlen(DEAD)))
	{
		pthread_mutex_lock(&p->data->printmutex);
		printf("%llu %i", get_time() - p->birth_time, p->id);
		printf("%s", action);
		pthread_mutex_unlock(&p->data->printmutex);
	}
	pthread_mutex_unlock(&p->data->monitor);
}
