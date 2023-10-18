/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 12:26:19 by fbohling          #+#    #+#             */
/*   Updated: 2023/10/18 14:48:47 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	actions(t_philo *p)
{
	take_forks(p);
	display_action(EAT, p);
	pthread_mutex_lock(&p->data->monitor);
	p->eat_stat = 1;
	pthread_mutex_unlock(&p->data->monitor);
	ft_usleep(p->data->eating_time);
	pthread_mutex_lock(&p->data->monitor);
	p->time_to_die = get_time() + p->data->death_time;
	p->eat_n++;
	p->eat_stat = 0;
	pthread_mutex_unlock(&p->data->monitor);
	drop_forks(p);
	display_action(SLEEP, p);
	ft_usleep(p->data->sleep_time);
}

void	take_forks(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(p->left);
		display_action(FORK, p);
		pthread_mutex_lock(p->right);
		display_action(FORK, p);
	}
	else
	{
		pthread_mutex_lock(p->right);
		display_action(FORK, p);
		pthread_mutex_lock(p->left);
		display_action(FORK, p);
	}
}

void	drop_forks(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		pthread_mutex_unlock(p->left);
		pthread_mutex_unlock(p->right);
	}
	else
	{
		pthread_mutex_unlock(p->right);
		pthread_mutex_unlock(p->left);
	}
}
