/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:19:41 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/15 15:45:38 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state_change(t_philo *philo, char *message)
{
	pthread_mutex_lock(philo->data->mutexes.print);
	printf("%ld %d %s\n", timestamp_get(), philo->id, message);
	pthread_mutex_unlock(philo->data->mutexes.print);
}
