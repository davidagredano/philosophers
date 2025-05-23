/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:31:50 by dagredan          #+#    #+#             */
/*   Updated: 2025/05/10 22:54:44 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	data_allocate(t_data *data, char *argv[])
{
	int	len;

	len = ft_atoi(argv[1]);
	data->mutexes.forks = (t_mutex *)malloc(len * sizeof(t_mutex));
	if (!data->mutexes.forks)
	{
		print_error("malloc failed for mutexes.forks in data_allocate");
		return (-1);
	}
	data->mutexes.philos = (t_mutex *)malloc(len * sizeof(t_mutex));
	if (!data->mutexes.philos)
	{
		print_error("malloc failed for mutexes.philos in data_allocate");
		return (-1);
	}
	data->philos.arr = (t_philo *)malloc(len * sizeof(t_philo));
	if (!data->philos.arr)
	{
		print_error("malloc failed for philos.arr in data_allocate");
		return (-1);
	}
	return (0);
}

void	data_init(t_data *data, int argc, char *argv[])
{
	int	len;

	len = ft_atoi(argv[1]);
	rules_init_data(data, argc, argv);
	philos_init_data(data, len);
}

void	data_free(t_data *data)
{
	if (data->mutexes.forks)
	{
		free(data->mutexes.forks);
		data->mutexes.forks = NULL;
	}
	if (data->mutexes.philos)
	{
		free(data->mutexes.philos);
		data->mutexes.philos = NULL;
	}
	if (data->philos.arr)
	{
		free(data->philos.arr);
		data->philos.arr = NULL;
	}
}
