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

int	philo_update_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex);
	philo->last_meal_time = get_current_time();
	if (philo->last_meal_time < 0)
		return (-1);
	pthread_mutex_unlock(philo->mutex);
	return (0);
}

static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_simulation_state(philo->data) == SETUP)
		;
	if (get_simulation_state(philo->data) == RUNNING)
	{
		if (philo_update_last_meal_time(philo) != 0)
			return (NULL);
		if (philo_initial_think(philo) != 0)
			return (NULL);
	}
	while (get_simulation_state(philo->data) == RUNNING)
	{
		if (philo_take_forks(philo) != 0)
			return (NULL);
		if (philo_eat(philo) != 0)
			return (NULL);
		if (philo_sleep(philo) != 0)
			return (NULL);
		if (philo_think(philo) != 0)
			return (NULL);
	}
	return (NULL);
}

int	philos_create_threads(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < data->philos.len)
	{
		philo = &data->philos.arr[i];
		if (pthread_create(&philo->thread, NULL, &philo_routine, philo) != 0)
			return (-1);
		philo->thread_created = 1;
		i++;
	}
	return (0);
}

void	philos_join_threads(t_data *data)
{
	int	i;

	if (data->philos.arr)
	{
		i = 0;
		while (i < data->philos.len)
		{
			if (data->philos.arr[i].thread_created)
				pthread_join(data->philos.arr[i].thread, NULL);
			i++;
		}
	}
}
