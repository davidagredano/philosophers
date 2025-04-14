/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:54:56 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/14 18:12:58 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_print(t_philo *philo)
{
	printf("  id: %d\n", philo->id);
	printf("  rules: %p\n", philo->rules);
	printf("  fork_left: %p\n", philo->fork_left);
	printf("  fork_right: %p\n", philo->fork_right);
	printf("  times_eaten: %d\n", philo->times_eaten);
	printf("  time_of_last_meal: %ld\n", philo->last_meal_time);
}

void	data_print(t_data *data)
{
	t_rules	rules;
	t_uint	i;

	rules = data->rules;
	printf("\ndata:\n");
	printf("  rules.time_to_die: %d\n", rules.time_to_die);
	printf("  rules.time_to_eat: %d\n", rules.time_to_eat);
	printf("  rules.time_to_sleep: %d\n", rules.time_to_sleep);
	if (rules.times_each_must_eat)
		printf("  rules.times_each_must_eat: %d\n", rules.times_each_must_eat);
	printf("  count: %d\n\n", data->philos.len);
	i = 0;
	while (i < data->philos.len)
	{
		printf("philosophers[%d]:\n", i);
		philo_print(&data->philos.arr[i]);
		printf("\n");
		i++;
	}
	i = 0;
	while (i < data->forks.len)
	{
		printf("forks[%d]: %p\n", i, &data->forks.arr[i]);
		i++;
	}
}
