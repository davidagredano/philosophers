/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:19:41 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/29 16:13:23 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state_change(t_philo *philo, char *message)
{
	long	elapsed_time;

	pthread_mutex_lock(philo->data->mutex);
	if (philo->data->rules.simulation_running == 1)
	{
		elapsed_time = get_current_time() - philo->data->rules.simulation_start;
		printf("%ld %d %s\n", elapsed_time, philo->id, message);
	}
	pthread_mutex_unlock(philo->data->mutex);
}
