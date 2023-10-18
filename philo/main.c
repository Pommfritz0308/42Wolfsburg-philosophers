/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:38:12 by fbohling          #+#    #+#             */
/*   Updated: 2023/10/12 14:18:52 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 2)
		return (0);
	handle_input(argv);
	format_input(argv, &data);
	if (data.size < 4 || data.size > 5)
	{
		free(data.arr);
		printf("\033[1;31mCHECK NUMBER OF ARGUMENTS!\033[0m\n");
		return (1);
	}
	init_data(&data);
	if (!alloc_struct(&data))
	{
		clean(&data);
		return (1);
	}
	philo(&data);
	pthread_mutex_destroy(&data.printmutex);
	free(data.tid);
	free(data.philos);
	free(data.forks);
	return (0);
}
