/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:19:41 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/29 19:28:17 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_state_change(t_philo *philo, char *message)
{
	long	current_time;
	long	elapsed_time;

	pthread_mutex_lock(&philo->data->mutexes.global);
	if (philo->data->rules.simulation_state != FINISHED)
	{
		current_time = get_current_time();
		if (current_time < 0)
			return (-1);
		elapsed_time = current_time - philo->data->rules.simulation_start;
		if (printf("%ld %d %s\n", elapsed_time, philo->id, message) < 0)
			return (-1);
	}
	pthread_mutex_unlock(&philo->data->mutexes.global);
	return (0);
}
