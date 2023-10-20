/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:43:13 by fbohling          #+#    #+#             */
/*   Updated: 2023/10/20 13:33:23 by fbohling         ###   ########.fr       */
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
		usleep(200);
	}
	return ;
}

void	display_action(char *action, t_philo *p)
{
	pthread_mutex_lock(&p->data->printmutex);
	if (!p->data->finished || !ft_strncmp(action, DEAD, ft_strlen(DEAD)))
	{
		ft_putnbr_unsigned(get_time() - p->birth_time);
		ft_putchar('\t');
		ft_putnbr(p->id);
		ft_putchar(' ');
		color(action);
		ft_putstr(action);
		write(1, RESET, ft_strlen(RESET));
	}
	pthread_mutex_unlock(&p->data->printmutex);
}

void	color(char *s)
{
	if (!ft_strncmp(s, THINK, ft_strlen(THINK)))
		write(1, YELLOW, ft_strlen(YELLOW));
	else if (!ft_strncmp(s, EAT, ft_strlen(EAT)))
		write(1, GREEN, ft_strlen(GREEN));
	else if (!ft_strncmp(s, FORK, ft_strlen(FORK)))
		write(1, MAGENTA, ft_strlen(MAGENTA));
	else if (!ft_strncmp(s, SLEEP, ft_strlen(SLEEP)))
		write(1, CYAN, ft_strlen(BLUE));
	else if (!ft_strncmp(s, DEAD, ft_strlen(DEAD)))
		write(1, RED, ft_strlen(RED));
}
