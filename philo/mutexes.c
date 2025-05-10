/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:12:21 by dagredan          #+#    #+#             */
/*   Updated: 2025/05/10 19:27:11 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutexes_init(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->mutexes.global, NULL) != 0)
		return (error(data, "pthread_mutex_init", "mutexes_init", 0));
	data->mutexes.global_initialized = 1;
	i = 0;
	while (i < data->philos.len)
	{
		if (pthread_mutex_init(&data->mutexes.forks[i], NULL) != 0)
			return (error(data, "pthread_mutex_init", "mutexes_init", 0));
		data->mutexes.forks_initialized++;
		i++;
	}
	i = 0;
	while (i < data->philos.len)
	{
		if (pthread_mutex_init(&data->mutexes.philos[i], NULL) != 0)
			return (error(data, "pthread_mutex_init", "mutexes_init", 0));
		data->mutexes.philos_initialized++;
		i++;
	}
	return (0);
}

void	mutexes_destroy(t_data *data)
{
	int	i;

	if (data->mutexes.global_initialized == 1)
	{
		pthread_mutex_destroy(&data->mutexes.global);
		data->mutexes.global_initialized = 0;
	}
	i = 0;
	while (i < data->philos.len && data->mutexes.forks_initialized > 0)
	{
		pthread_mutex_destroy(&data->mutexes.forks[i]);
		data->mutexes.forks_initialized--;
		i++;
	}
	i = 0;
	while (i < data->philos.len && data->mutexes.philos_initialized > 0)
	{
		pthread_mutex_destroy(&data->mutexes.philos[i]);
		data->mutexes.philos_initialized--;
		i++;
	}
}
