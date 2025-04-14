/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:44:25 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/14 15:02:51 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(t_philo *philo)
{
	printf("%ld %d is thinking\n", timestamp_get(), philo->id);
}

void	philo_take_forks(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->fork_right);
		printf("%ld %d has taken a fork\n", timestamp_get(), philo->id);
		pthread_mutex_lock(philo->fork_left);
		printf("%ld %d has taken a fork\n", timestamp_get(), philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->fork_left);
		printf("%ld %d has taken a fork\n", timestamp_get(), philo->id);
		pthread_mutex_lock(philo->fork_right);
		printf("%ld %d has taken a fork\n", timestamp_get(), philo->id);
	}
}

void	philo_eat(t_philo *philo)
{
	philo->time_of_last_meal = timestamp_get();
	printf("%ld %d is eating\n", philo->time_of_last_meal, philo->id);
	usleep(philo->rules->time_to_eat * 1000);
	philo->times_eaten++;
}

void	philo_leave_forks(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
	}
	else
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
	}
}

void	philo_sleep(t_philo *philo)
{
	printf("%ld %d is sleeping\n", timestamp_get(), philo->id);
	usleep(philo->rules->time_to_sleep * 1000);
}
