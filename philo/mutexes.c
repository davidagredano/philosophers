/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:12:21 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/15 17:19:05 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutexes_init(t_data *data)
{
	pthread_mutex_init(data->mutexes.rules, NULL);
}

void	mutexes_free(t_data *data)
{
	if (data->mutexes.rules)
	{
		free(data->mutexes.rules);
		data->mutexes.rules = NULL;
	}
}

void	mutexes_cleanup(t_data *data)
{
	if (data->mutexes.rules)
		pthread_mutex_destroy(data->mutexes.rules);
	mutexes_free(data);
}
