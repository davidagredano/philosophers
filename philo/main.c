/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:08:15 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/15 03:07:25 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	arguments_validate(int argc)
{
	if (argc < 5)
	{
		printf("Too few arguments\n");
		return (-1);
	}
	else if (argc > 6)
	{
		printf("Too many arguments\n");
		return (-1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (arguments_validate(argc) != 0)
		return (EXIT_FAILURE);
	if (data_malloc(&data, argv) != 0)
	{
		data_free(&data);
		return (EXIT_FAILURE);
	}
	data_init(&data, argc, argv);
	set_simulation_running(&data.rules, 1);
	data_cleanup(&data);
	return (EXIT_SUCCESS);
}
