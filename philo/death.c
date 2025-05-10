/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 23:39:23 by dagredan          #+#    #+#             */
/*   Updated: 2025/05/10 19:23:19 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (get_simulation_state(data) == RUNNING)
		precise_usleep(data->rules.time_to_die * 1000);
	while (get_simulation_state(data) == RUNNING)
	{
		i = 0;
		while (get_simulation_state(data) == RUNNING && i < data->philos.len)
		{
			if (philo_starved(&data->philos.arr[i]))
			{
				philo_handle_state_change(&data->philos.arr[i], "died");
				return (NULL);
			}
			i++;
		}
		usleep(2000);
	}
	return (NULL);
}

int	death_create_thread(t_data *data)
{
	if (pthread_create(&data->death, NULL, &death_routine, data) != 0)
		return (error(data, "pthread_create", "death_create_thread", 1));
	data->death_created = 1;
	return (0);
}

void	death_join_thread(t_data *data)
{
	if (data->death_created)
		pthread_join(data->death, NULL);
}
