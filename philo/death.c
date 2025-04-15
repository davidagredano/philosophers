/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 23:39:23 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/15 17:18:40 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	handle_death(t_philo *philo)
{
	pthread_mutex_lock(philo->data->mutexes.rules);
	if (philo->data->rules.simulation_running == 1)
	{
		philo->data->rules.simulation_running = 0;
		pthread_mutex_lock(philo->data->mutexes.print);
		printf("%ld %d %s\n", timestamp_get(), philo->id, "died");
		pthread_mutex_unlock(philo->data->mutexes.print);
	}
	pthread_mutex_unlock(philo->data->mutexes.rules);
}

static int	philo_starved(t_philo *philo)
{
	long	now;
	long	time_since_last_meal;

	now = timestamp_get();
	pthread_mutex_lock(philo->mutex);
	time_since_last_meal = now - philo->last_meal_time;
	pthread_mutex_unlock(philo->mutex);
	return (time_since_last_meal > philo->data->rules.time_to_die);
}

static void	*death_routine(void *arg)
{
	t_data	*data;
	t_uint	i;

	data = (t_data *)arg;
	while (!is_simulation_running(data))
		usleep(1000);
	while (is_simulation_running(data))
	{
		usleep(1000);
		i = 0;
		while (is_simulation_running(data) && i < data->philos.len)
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
