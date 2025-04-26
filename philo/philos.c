/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:14:05 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/26 12:03:03 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!is_simulation_running(philo->data))
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
	while (is_simulation_running(philo->data))
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

void	philos_init(t_data *data, int len)
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
		philo->mutex = &data->philos.mtx_arr[i];
		philo->id = i + 1;
		philo->fork_left = &data->forks.arr[i];
		if (i == len - 1)
			philo->fork_right = &data->forks.arr[0];
		else
			philo->fork_right = &data->forks.arr[i + 1];
		pthread_mutex_init(philo->mutex, NULL);
		pthread_create(&philo->thread, NULL, &philo_routine, philo);
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
	int	i;

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
