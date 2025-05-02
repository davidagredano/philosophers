/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:54:56 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/29 19:08:12 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_print(t_philo *philo)
{
	printf("  data: %p\n", philo->data);
	printf("  mutex: %p\n", philo->mutex);
	printf("  id: %d\n", philo->id);
	printf("  fork_left: %p\n", philo->fork_left);
	printf("  fork_right: %p\n", philo->fork_right);
	printf("  times_eaten: %d\n", philo->times_eaten);
	printf("  time_of_last_meal: %ld\n", philo->last_meal_time);
}

void	data_print(t_data *data)
{
	t_rules	rules;
	int		i;

	rules = data->rules;
	printf("\ndata:\n");
	printf("  rules.time_to_die: %d\n", rules.time_to_die);
	printf("  rules.time_to_eat: %d\n", rules.time_to_eat);
	printf("  rules.time_to_sleep: %d\n", rules.time_to_sleep);
	if (rules.meal_goal)
		printf("  rules.meal_goal: %d\n", rules.meal_goal);
	printf("  count: %d\n\n", data->philos.len);
	i = 0;
	while (i < data->philos.len)
	{
		printf("philosophers[%d]:\n", i);
		philo_print(&data->philos.arr[i]);
		printf("\n");
		i++;
	}
}

void	print_mutexes(t_data *data)
{
	t_mutexes	mutexes;

	mutexes = data->mutexes;
	printf("Mutexes:\n");
	printf("  data.mutexes.global: %p\n", &mutexes.global);
	printf("  data.mutexes.forks: %p\n", mutexes.forks);
	printf("  data.mutexes.philos: %p\n", mutexes.philos);
	printf("\n");
}

void	print_sizes(int len)
{
	printf("t_data size: %lu\n", sizeof(t_data));
	printf("t_philo size: %lu\n", sizeof(t_philo));
	printf("pthread_t size: %lu\n", sizeof(pthread_t));
	printf("pthread_mutex_t size: %lu\n", sizeof(pthread_mutex_t));
	printf("data->forks.arr size: %lu\n", len * sizeof(t_mutex));
	printf("data->philos.arr size: %lu\n", len * sizeof(t_philo));
	printf("data->philos.mtx_arr size: %lu\n", len * sizeof(t_mutex));
}
