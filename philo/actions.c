/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:44:25 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/15 15:45:16 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(t_philo *philo)
{
	print_state_change(philo, "is thinking");
}

void	philo_take_forks(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->fork_right);
		print_state_change(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_left);
		print_state_change(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->fork_left);
		print_state_change(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_right);
		print_state_change(philo, "has taken a fork");
	}
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex);
	philo->last_meal_time = timestamp_get();
	print_state_change(philo, "is eating");
	pthread_mutex_unlock(philo->mutex);
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
	print_state_change(philo, "is sleeping");
	usleep(philo->rules->time_to_sleep * 1000);
}
