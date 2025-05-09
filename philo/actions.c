/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:44:25 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/26 12:02:57 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_initial_think(t_philo *philo)
{
	if (philo->data->philos.len % 2 == 0 && philo->id % 2 == 0)
		precise_usleep(philo->data->rules.time_to_eat / 2 * 1000);
	else if (philo->data->philos.len % 2 == 1 && philo->id % 3 == 1)
		precise_usleep(philo->data->rules.time_to_eat / 2 * 1000);
	else if (philo->data->philos.len % 2 == 1 && philo->id % 3 == 2)
		precise_usleep(philo->data->rules.time_to_eat * 3 / 2 * 1000);
}

void	philo_think(t_philo *philo)
{
	print_state_change(philo, "is thinking");
	if (philo->data->philos.len % 2 == 1)
		precise_usleep(philo->data->rules.time_to_eat / 2 * 1000);
}

int	philo_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	print_state_change(philo, "has taken a fork");
	if (philo->fork_right == philo->fork_left)
	{
		pthread_mutex_unlock(philo->fork_left);
		return (-1);
	}
	pthread_mutex_lock(philo->fork_right);
	print_state_change(philo, "has taken a fork");
	return (0);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(philo->mutex);
	print_state_change(philo, "is eating");
	precise_usleep(philo->data->rules.time_to_eat * 1000);
	pthread_mutex_lock(philo->mutex);
	philo->times_eaten++;
	pthread_mutex_unlock(philo->mutex);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

void	philo_sleep(t_philo *philo)
{
	print_state_change(philo, "is sleeping");
	precise_usleep(philo->data->rules.time_to_sleep * 1000);
}
