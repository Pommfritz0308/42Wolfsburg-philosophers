/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:38:12 by fbohling          #+#    #+#             */
/*   Updated: 2023/10/20 17:08:03 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 2)
		return (0);
	if (!handle_input(argv))
		return (1);
	if (!format_input(argv, &data) || data.size < 4 || data.size > 5)
	{
		if (data.size < 4 || data.size > 5)
			printf("\033[1;31mCHECK NUMBER OF ARGUMENTS!\033[0m\n");
		free(data.arr);
		return (1);
	}
	init_data(&data);
	if (!alloc_struct(&data))
	{
		clean(&data);
		return (1);
	}
	philo(&data);
	clean(&data);
	return (0);
}
