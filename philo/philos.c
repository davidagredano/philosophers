/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:14:05 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/15 03:07:33 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	while (!is_simulation_running(philo->rules))
		usleep(100);
	pthread_mutex_lock(philo->mutex);
	philo->last_meal_time = timestamp_get();
	pthread_mutex_unlock(philo->mutex);
	while (is_simulation_running(philo->rules))
	{
		philo_think(philo);
		philo_take_forks(philo);
		philo_eat(philo);
		philo_leave_forks(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

void	philos_init(t_data *data, t_uint len)
{
	t_uint	i;
	t_philo	*curr_philo;

	i = 0;
	data->philos.len = len;
	while (i < len)
	{
		curr_philo = &data->philos.arr[i];
		memset(curr_philo, 0, sizeof(t_philo));
		curr_philo->id = i + 1;
		curr_philo->rules = &data->rules;
		curr_philo->fork_left = &data->forks.arr[i];
		if (i == len - 1)
			curr_philo->fork_right = &data->forks.arr[0];
		else
			curr_philo->fork_right = &data->forks.arr[i + 1];
		curr_philo->mutex = &data->philos.mtx_arr[i];
		pthread_mutex_init(curr_philo->mutex, NULL);
		pthread_create(&curr_philo->thread, NULL, &philo_routine, curr_philo);
		i++;
	}
}

void	philos_free(t_data *data)
{
	if (data->philos.arr)
	{
		free(data->philos.arr);
		data->philos.arr = NULL;
		free(data->philos.mtx_arr);
		data->philos.mtx_arr = NULL;
	}
}

void	philos_cleanup(t_data *data)
{
	t_uint	i;

	if (data->philos.arr)
	{
		i = 0;
		while (i < data->philos.len)
		{
			pthread_join(data->philos.arr[i].thread, NULL);
			pthread_mutex_destroy(data->philos.arr[i].mutex);
			i++;
		}
	}
	philos_free(data);
}
