/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:08:15 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/29 19:08:15 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	program_cleanup(t_data *data)
{
	threads_join(data);
	mutexes_destroy(data);
	data_free(data);
}

static void	simulation_start(t_data *data)
{
	data->rules.simulation_start = get_current_time();
	set_simulation_running(data, 1);
}

static int	program_init(t_data *data, int argc, char *argv[])
{
	if (data_init(data, argc, argv) != 0)
		return (-1);
	if (mutexes_init(data) != 0)
	{
		mutexes_destroy(data);
		data_free(data);
		return (-1);
	}
	threads_create(data);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (arguments_validate(argc, argv) != 0)
		return (EXIT_FAILURE);
	if (program_init(&data, argc, argv) != 0)
		return (EXIT_FAILURE);
	simulation_start(&data);
	program_cleanup(&data);
	return (EXIT_SUCCESS);
}
