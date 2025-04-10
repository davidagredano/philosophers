/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:08:15 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/10 15:14:42 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	data_destroy(t_data *data)
{
	if (data->philosophers)
		free(data->philosophers);
	if (data->forks)
		free(data->forks);
}

static void	philo_init(t_data *data, t_uint i)
{
	memset(&data->philosophers[i], 0, sizeof(t_philo));
	data->philosophers[i].number = i + 1;
	data->philosophers[i].rules = &data->rules;
	data->philosophers[i].fork_left = &data->forks[i];
	if (i == data->count - 1)
		data->philosophers[i].fork_right = &data->forks[0];
	else
		data->philosophers[i].fork_right = &data->forks[i + 1];
}

static int	data_init(t_data *data, int argc, char *argv[])
{
	t_uint	i;

	memset(data, 0, sizeof(t_data));
	data->rules.time_to_die = ft_atoi(argv[2]);
	data->rules.time_to_eat = ft_atoi(argv[3]);
	data->rules.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->rules.times_each_must_eat = ft_atoi(argv[5]);
	data->count = ft_atoi(argv[1]);
	data->philosophers = (t_philo *)malloc(data->count * sizeof(t_philo));
	if (!data->philosophers)
		return (-1);
	data->forks = (char *)malloc(data->count * sizeof(char));
	if (!data->forks)
		return (-1);
	i = 0;
	while (i < data->count)
	{
		philo_init(data, i);
		i++;
	}
	return (0);
}

static int	arguments_validate(int argc)
{
	if (argc < 5)
	{
		printf("Too few arguments\n");
		return (-1);
	}
	else if (argc > 6)
	{
		printf("Too many arguments\n");
		return (-1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (arguments_validate(argc) != 0)
		return (EXIT_FAILURE);
	if (data_init(&data, argc, argv) != 0)
	{
		data_destroy(&data);
		return (EXIT_FAILURE);
	}
	if (threads_create(&data) != 0)
		data_destroy(&data);
	threads_join(&data);
	data_destroy(&data);
	return (EXIT_SUCCESS);
}
