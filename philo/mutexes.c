/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:12:21 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/29 16:13:18 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutexes_init(t_data *data)
{
	pthread_mutex_init(data->mutex, NULL);
}

void	mutexes_free(t_data *data)
{
	if (data->mutex)
	{
		free(data->mutex);
		data->mutex = NULL;
	}
}

void	mutexes_cleanup(t_data *data)
{
	if (data->mutex)
		pthread_mutex_destroy(data->mutex);
	mutexes_free(data);
}
