/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 23:39:23 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/15 03:07:22 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	handle_death(t_philo *philo)
{
	pthread_mutex_lock(philo->rules->mutex);
	if (philo->rules->simulation_running == 1)
	{
		philo->rules->simulation_running = 0;
		printf("%ld %d died\n", timestamp_get(), philo->id);
	}
	pthread_mutex_unlock(philo->rules->mutex);
}

static int	philo_starved(t_philo *philo)
{
	long	now;
	long	time_since_last_meal;

	now = timestamp_get();
	pthread_mutex_lock(philo->mutex);
	time_since_last_meal = now - philo->last_meal_time;
	pthread_mutex_unlock(philo->mutex);
	return (time_since_last_meal > philo->rules->time_to_die);
}

static void	*death_routine(void *arg)
{
	t_data	*data;
	t_uint	i;

	data = (t_data *)arg;
	while (!is_simulation_running(&data->rules))
		usleep(1000);
	while (is_simulation_running(&data->rules))
	{
		usleep(1000);
		i = 0;
		while (is_simulation_running(&data->rules) && i < data->philos.len)
		{
			if (philo_starved(&data->philos.arr[i]))
			{
				handle_death(&data->philos.arr[i]);
				return ((void *)0);
			}
			i++;
		}
	}
	return ((void *)0);
}

void	death_init(t_data *data)
{
	pthread_create(&data->death, NULL, &death_routine, data);
}

void	death_cleanup(t_data *data)
{
	pthread_join(data->death, NULL);
}
