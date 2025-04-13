/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:14:05 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/13 17:01:20 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	timestamp_get(void)
{
	struct timeval	timeval;

	if (gettimeofday(&timeval, NULL) != 0)
		return (-1);
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000));
}

static void	*routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	philo->time_of_last_meal = timestamp_get();
	while (philo->times_eaten < philo->rules->times_each_must_eat)
	{
		philo_think(philo);
		philo_take_forks(philo);
		philo_eat(philo);
		philo_leave_forks(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

int	threads_create(t_data *data)
{
	t_uint	i;

	i = 0;
	while (i < data->count)
	{
		if (pthread_create(&data->philosophers[i].thread, NULL,
				&routine, &data->philosophers[i]) != 0)
		{
			while (i > 0)
			{
				i--;
				pthread_join(data->philosophers[i].thread, NULL);
			}
			return (-1);
		}
		i++;
	}
	return (0);
}

void	threads_join(t_data *data)
{
	t_uint	i;

	i = 0;
	while (i < data->count)
	{
		pthread_join(data->philosophers[i].thread, NULL);
		i++;
	}
}
