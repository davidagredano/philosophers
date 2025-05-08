/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:14:05 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/29 19:08:22 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philos_init_data(t_data *data, int len)
{
	t_philo	*philo;
	int		i;

	i = 0;
	data->philos.len = len;
	while (i < len)
	{
		philo = &data->philos.arr[i];
		memset(philo, 0, sizeof(t_philo));
		philo->data = data;
		philo->mutex = &data->mutexes.philos[i];
		philo->id = i + 1;
		philo->fork_left = &data->mutexes.forks[i];
		if (i == len - 1)
			philo->fork_right = &data->mutexes.forks[0];
		else
			philo->fork_right = &data->mutexes.forks[i + 1];
		i++;
	}
}

static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_simulation_state(philo->data) == SETUP)
		;
	pthread_mutex_lock(philo->mutex);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(philo->mutex);
	if (philo->data->philos.len % 2 == 0 && philo->id % 2 == 0)
		precise_usleep(philo->data->rules.time_to_eat / 2 * 1000);
	else if (philo->data->philos.len % 2 == 1 && philo->id % 3 == 1)
		usleep(philo->data->rules.time_to_eat / 2 * 1000);
	else if (philo->data->philos.len % 2 == 1 && philo->id % 3 == 2)
		usleep(philo->data->rules.time_to_eat * 3 / 2 * 1000);
	while (get_simulation_state(philo->data) == RUNNING)
	{
		philo_think(philo);
		if (philo_take_forks(philo) == -1)
			return (NULL);
		philo_eat(philo);
		philo_leave_forks(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

void	philos_create_threads(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < data->philos.len)
	{
		philo = &data->philos.arr[i];
		pthread_create(&philo->thread, NULL, &philo_routine, philo);
		i++;
	}
}

void	philos_join_threads(t_data *data)
{
	int	i;

	if (data->philos.arr)
	{
		i = 0;
		while (i < data->philos.len)
		{
			pthread_join(data->philos.arr[i].thread, NULL);
			i++;
		}
	}
}
