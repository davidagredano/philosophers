/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:37:07 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/14 15:03:17 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	timestamp_get(void)
{
	struct timeval	timeval;

	if (gettimeofday(&timeval, NULL) != 0)
		return (-1);
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000));
}
