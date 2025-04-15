/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 02:10:17 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/15 03:07:46 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	rules_init(t_data *data, int argc, char *argv[])
{
	data->rules.time_to_die = ft_atoi(argv[2]);
	data->rules.time_to_eat = ft_atoi(argv[3]);
	data->rules.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->rules.times_each_must_eat = ft_atoi(argv[5]);
	pthread_mutex_init(data->rules.mutex, NULL);
	set_simulation_running(&data->rules, 0);
}

void	rules_free(t_data *data)
{
	if (data->rules.mutex)
	{
		free(data->rules.mutex);
		data->rules.mutex = NULL;
	}
}

void	rules_cleanup(t_data *data)
{
	if (data->rules.mutex)
		pthread_mutex_destroy(data->rules.mutex);
	rules_free(data);
}

int	is_simulation_running(t_rules *rules)
{
	int	simulation_running;

	pthread_mutex_lock(rules->mutex);
	simulation_running = rules->simulation_running;
	pthread_mutex_unlock(rules->mutex);
	return (simulation_running);
}

void	set_simulation_running(t_rules *rules, int value)
{
	pthread_mutex_lock(rules->mutex);
	rules->simulation_running = value;
	pthread_mutex_unlock(rules->mutex);
}
