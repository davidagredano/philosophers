/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:44:25 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/13 17:01:54 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(t_philo *philo)
{
	printf("%ld %d is thinking\n", timestamp_get(), philo->number);
}

void	philo_take_forks(t_philo *philo)
{
	if (philo->number % 2 == 1)
	{
		pthread_mutex_lock(philo->fork_right);
		printf("%ld %d has taken a fork\n", timestamp_get(), philo->number);
		pthread_mutex_lock(philo->fork_left);
		printf("%ld %d has taken a fork\n", timestamp_get(), philo->number);
	}
	else
	{
		pthread_mutex_lock(philo->fork_left);
		printf("%ld %d has taken a fork\n", timestamp_get(), philo->number);
		pthread_mutex_lock(philo->fork_right);
		printf("%ld %d has taken a fork\n", timestamp_get(), philo->number);
	}
}

void	philo_eat(t_philo *philo)
{
	philo->time_of_last_meal = timestamp_get();
	printf("%ld %d is eating\n", philo->time_of_last_meal, philo->number);
	usleep(philo->rules->time_to_eat * 1000);
}

void	philo_leave_forks(t_philo *philo)
{
	if (philo->number % 2 == 1)
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
	printf("%ld %d is sleeping\n", timestamp_get(), philo->number);
	usleep(philo->rules->time_to_sleep * 1000);
}
