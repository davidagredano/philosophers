/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:40:36 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/29 19:08:17 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	all_philos_finished(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (get_simulation_state(data) == RUNNING && i < data->philos.len)
	{
		philo = &data->philos.arr[i];
		if (!philo->is_full)
		{
			pthread_mutex_lock(philo->mutex);
			philo->is_full = philo->times_eaten >= data->rules.meal_goal;
			pthread_mutex_unlock(philo->mutex);
			if (!philo->is_full)
				return (0);
		}
		i++;
	}
	return (1);
}

static void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (get_simulation_state(data) == SETUP)
		;
	if (get_simulation_state(data) == RUNNING)
		precise_usleep(data->rules.time_to_eat * 1000);
	while (get_simulation_state(data) == RUNNING)
	{
		if (all_philos_finished(data))
		{
			set_simulation_state(data, FINISHED);
			return (NULL);
		}
		usleep(2000);
	}
	return (NULL);
}

int	monitor_create_thread(t_data *data)
{
	if (data->rules.meal_goal > 0)
	{
		if (pthread_create(&data->monitor, NULL, &monitor_routine, data) != 0)
			return (-1);
		data->monitor_created = 1;
	}
	return (0);
}

void	monitor_join_thread(t_data *data)
{
	if (data->monitor_created)
		pthread_join(data->monitor, NULL);
}
