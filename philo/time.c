/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:37:07 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/25 11:26:22 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(void)
{
	struct timeval	timeval;

	if (gettimeofday(&timeval, NULL) != 0)
		return (-1);
	return ((timeval.tv_sec * 1000L) + (timeval.tv_usec / 1000L));
}

static long	get_current_time_usec(void)
{
	struct timeval	timeval;

	if (gettimeofday(&timeval, NULL) != 0)
		return (-1);
	return ((timeval.tv_sec * 1000000L) + timeval.tv_usec);
}

int	precise_usleep(int usec)
{
	long	now;
	long	end;

	now = get_current_time_usec();
	if (now < 0)
		return (-1);
	end = now + usec;
	if (usec > SPINLOCK_THRESHOLD_USEC)
	{
		if (usleep(usec - SPINLOCK_THRESHOLD_USEC) != 0)
			return (-1);
	}
	while (now < end)
	{
		now = get_current_time_usec();
		if (now < 0)
			return (-1);
	}
	return (0);
}
