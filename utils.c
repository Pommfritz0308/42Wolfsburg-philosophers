/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 18:36:57 by fbohling          #+#    #+#             */
/*   Updated: 2023/10/17 18:12:58 by fbohling         ###   ########.fr       */
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

void	init_data(t_data *data)
{
	int	i;

	i = 0;
	data->philo_n = data->arr[0];
	data->death_time = data->arr[1];
	data->eating_time = data->arr[2];
	data->sleep_time = data->arr[3];
	data->dead = 0;
	if (data->size == 5)
		data->meal_n = data->arr[4];
	pthread_mutex_init(&data->printmutex, NULL);
	pthread_mutex_init(&data->lock, NULL);
	pthread_mutex_init(&data->death, NULL);
	pthread_mutex_init(&data->finish, NULL);
	free(data->arr);
}

void	init_threads(t_data *data)
{
	int				i;
	pthread_t		supervisor_tid;

	i = 0;
	while (i < data->philo_n)
	{
		data->philos[i].birth_time = get_time();
		data->philos[i].time_to_die = data->philos[i].birth_time + data->death_time;
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philos[i]))
			return (clean(data));
		i++;
	}
	pthread_create(&supervisor_tid, NULL, &supervisor, (void *)data);
	pthread_join(supervisor_tid, NULL);
	end_sim(data);
	return ;
}

void	init_philos(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->philo_n)
	{
		d->philos[i].id = i + 1;
		d->philos[i].data = d;
		d->philos[i].status = 0;
		d->philos[i].eat_n = 0;
		d->philos[i].eat_stat = 0;
		pthread_mutex_init(&d->philos[i].lock, NULL);
		i++;
	}
}

void	clean(t_data *data)
{
	free(data->tid);
	free(data->philos);
	free(data->forks);
}
