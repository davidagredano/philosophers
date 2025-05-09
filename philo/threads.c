/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:57:16 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/29 19:08:27 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	threads_create(t_data *data)
{
	if (philos_create_threads(data) != 0)
		return (-1);
	death_create_thread(data);
	monitor_create_thread(data);
	return (0);
}

void	threads_join(t_data *data)
{
	monitor_join_thread(data);
	death_join_thread(data);
	philos_join_threads(data);
}
