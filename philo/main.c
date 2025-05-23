/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:08:15 by dagredan          #+#    #+#             */
/*   Updated: 2025/05/10 19:07:57 by dagredan         ###   ########.fr       */
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
	set_simulation_state(data, RUNNING);
}

static int	program_init(t_data *data, int argc, char *argv[])
{
	memset(data, 0, sizeof(t_data));
	if (data_allocate(data, argv) != 0)
	{
		data_free(data);
		return (-1);
	}
	data_init(data, argc, argv);
	if (mutexes_init(data) != 0)
	{
		mutexes_destroy(data);
		data_free(data);
		return (-1);
	}
	if (threads_create(data) != 0)
	{
		threads_join(data);
		mutexes_destroy(data);
		data_free(data);
		return (-1);
	}
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
