/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 23:39:23 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/29 19:28:10 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	handle_death(t_philo *philo)
{
	long	elapsed_time;

	pthread_mutex_lock(&philo->data->mutexes.global);
	if (philo->data->rules.simulation_state == RUNNING)
	{
		philo->data->rules.simulation_state = FINISHED;
		elapsed_time = get_current_time() - philo->data->rules.simulation_start;
		printf("%ld %d %s\n", elapsed_time, philo->id, "died");
	}
	pthread_mutex_unlock(&philo->data->mutexes.global);
}

static int	philo_starved(t_philo *philo)
{
	long	now;
	long	time_since_last_meal;

	now = get_current_time();
	pthread_mutex_lock(philo->mutex);
	time_since_last_meal = now - philo->last_meal_time;
	pthread_mutex_unlock(philo->mutex);
	return (time_since_last_meal > philo->data->rules.time_to_die);
}

static void	*death_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (get_simulation_state(data) == SETUP)
		;
	precise_usleep(data->rules.time_to_die * 1000);
	while (get_simulation_state(data) == RUNNING)
	{
		i = 0;
		while (get_simulation_state(data) == RUNNING && i < data->philos.len)
		{
			if (philo_starved(&data->philos.arr[i]))
			{
				handle_death(&data->philos.arr[i]);
				return ((void *)0);
			}
			i++;
		}
		usleep(2000);
	}
	return ((void *)0);
}

void	death_create_thread(t_data *data)
{
	pthread_create(&data->death, NULL, &death_routine, data);
}

void	death_join_thread(t_data *data)
{
	pthread_join(data->death, NULL);
}
