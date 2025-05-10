/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:44:25 by dagredan          #+#    #+#             */
/*   Updated: 2025/05/11 00:06:11 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_initial_think(t_philo *philo)
{
	if (philo->data->philos.len % 2 == 0)
	{
		if (philo->id % 2 == 0)
		{
			if (philo_handle_state_change(philo, "is thinking") != 0)
				return (-1);
			precise_usleep(philo->data->rules.time_to_eat / 2 * 1000);
		}
	}
	else if (philo->data->philos.len % 2 == 1)
	{
		if (philo->id % 3 == 1)
		{
			if (philo_handle_state_change(philo, "is thinking") != 0)
				return (-1);
			precise_usleep(philo->data->rules.time_to_eat / 2 * 1000);
		}
		else if (philo->id % 3 == 2)
		{
			if (philo_handle_state_change(philo, "is thinking") != 0)
				return (-1);
			precise_usleep(philo->data->rules.time_to_eat * 3 / 2 * 1000);
		}
	}
	return (0);
}

int	philo_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	if (philo_handle_state_change(philo, "has taken a fork") != 0)
	{
		pthread_mutex_unlock(philo->fork_left);
		return (-1);
	}
	if (philo->fork_right == philo->fork_left)
	{
		pthread_mutex_unlock(philo->fork_left);
		return (-1);
	}
	pthread_mutex_lock(philo->fork_right);
	if (philo_handle_state_change(philo, "has taken a fork") != 0)
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return (-1);
	}
	return (0);
}

int	philo_eat(t_philo *philo)
{
	philo_update_last_meal_time(philo);
	if (philo_handle_state_change(philo, "is eating") != 0)
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return (-1);
	}
	precise_usleep(philo->data->rules.time_to_eat * 1000);
	pthread_mutex_lock(philo->mutex);
	philo->times_eaten++;
	pthread_mutex_unlock(philo->mutex);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (philo_handle_state_change(philo, "is sleeping") != 0)
		return (-1);
	precise_usleep(philo->data->rules.time_to_sleep * 1000);
	return (0);
}

int	philo_think(t_philo *philo)
{
	if (philo_handle_state_change(philo, "is thinking") != 0)
		return (-1);
	if (philo->data->philos.len % 2 == 1)
		precise_usleep(philo->data->rules.time_to_eat / 2 * 1000);
	return (0);
}
