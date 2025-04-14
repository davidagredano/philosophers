/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:43:19 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/14 15:03:04 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	forks_init(t_data *data, t_uint len)
{
	t_uint	i;

	i = 0;
	data->forks.len = len;
	while (i < len)
	{
		pthread_mutex_init(&data->forks.arr[i], NULL);
		i++;
	}
}

void	forks_free(t_data *data)
{
	if (data->forks.arr)
	{
		free(data->forks.arr);
		data->forks.arr = NULL;
	}
}

void	forks_cleanup(t_data *data)
{
	t_uint	i;

	if (data->forks.arr)
	{
		i = 0;
		while (i < data->forks.len)
		{
			pthread_mutex_destroy(&data->forks.arr[i]);
			i++;
		}
	}
	forks_free(data);
}
