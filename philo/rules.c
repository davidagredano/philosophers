/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 02:10:17 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/29 19:28:19 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	rules_init_data(t_data *data, int argc, char *argv[])
{
	data->rules.time_to_die = ft_atoi(argv[2]);
	data->rules.time_to_eat = ft_atoi(argv[3]);
	data->rules.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->rules.meal_goal = ft_atoi(argv[5]);
}

int	is_simulation_running(t_data *data)
{
	int	simulation_running;

	pthread_mutex_lock(&data->mutexes.global);
	simulation_running = data->rules.simulation_running;
	pthread_mutex_unlock(&data->mutexes.global);
	return (simulation_running);
}

void	set_simulation_running(t_data *data, int value)
{
	pthread_mutex_lock(&data->mutexes.global);
	data->rules.simulation_running = value;
	pthread_mutex_unlock(&data->mutexes.global);
}
