/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:47:12 by fbohling          #+#    #+#             */
/*   Updated: 2023/10/20 16:57:39 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_threads(t_data *data)
{
	int				i;
	pthread_t		supervisor_tid;
	pthread_t		finished_tid;

	i = 0;
	if (data->size == 5)
		pthread_create(&finished_tid, NULL, &check_finished, (void *)data);
	while (i < data->philo_n)
	{
		data->philos[i].birth_time = get_time();
		data->philos[i].time_to_die = data->philos[i].birth_time
			+ data->death_time;
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philos[i]))
			return (clean(data));
		i++;
	}
	pthread_create(&supervisor_tid, NULL, &check_death, (void *)data);
	if (data->size == 5)
		pthread_join(finished_tid, NULL);
	pthread_join(supervisor_tid, NULL);
	end_sim(data);
	return ;
}
