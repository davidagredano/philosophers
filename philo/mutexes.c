/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:12:21 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/29 19:28:13 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutexes_init(t_data *data)
{
	int	i;

	pthread_mutex_init(&data->mutexes.global, NULL);
	i = 0;
	while (i < data->philos.len)
	{
		pthread_mutex_init(&data->mutexes.forks[i], NULL);
		pthread_mutex_init(&data->mutexes.philos[i], NULL);
		i++;
	}
}

void	mutexes_destroy(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->mutexes.global);
	i = 0;
	while (i < data->philos.len)
	{
		pthread_mutex_destroy(&data->mutexes.forks[i]);
		pthread_mutex_destroy(&data->mutexes.philos[i]);
		i++;
	}
}
