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

void	threads_create(t_data *data)
{
	philos_create_threads(data);
	death_create_thread(data);
	monitor_create_thread(data);
}

void	threads_join(t_data *data)
{
	monitor_join_thread(data);
	death_join_thread(data);
	philos_join_threads(data);
}
