/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:40:36 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/25 11:26:14 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	all_philos_finished(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (is_simulation_running(data) && i < data->philos.len)
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
	while (!is_simulation_running(data))
		;
	precise_usleep(data->rules.time_to_eat * 1000);
	while (is_simulation_running(data))
	{
		if (all_philos_finished(data))
		{
			set_simulation_running(data, 0);
			return ((void *)0);
		}
		usleep(2000);
	}
	return ((void *)0);
}

void	monitor_init(t_data *data)
{
	if (data->rules.meal_goal > 0)
		pthread_create(&data->monitor, NULL, &monitor_routine, data);
}

void	monitor_cleanup(t_data *data)
{
	if (data->rules.meal_goal > 0)
		pthread_join(data->monitor, NULL);
}
