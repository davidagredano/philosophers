/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:14:05 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/10 15:14:46 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	printf("%d has started\n", philo->number);
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
