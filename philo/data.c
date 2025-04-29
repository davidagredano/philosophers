/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:31:50 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/29 19:28:08 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	data_allocate(t_data *data, char *argv[])
{
	int	len;

	len = ft_atoi(argv[1]);
	data->mutexes.forks = (t_mutex *)malloc(len * sizeof(t_mutex));
	if (!data->mutexes.forks)
		return (-1);
	data->mutexes.philos = (t_mutex *)malloc(len * sizeof(t_mutex));
	if (!data->mutexes.philos)
		return (-1);
	data->philos.arr = (t_philo *)malloc(len * sizeof(t_philo));
	if (!data->philos.arr)
		return (-1);
	return (0);
}

int	data_init(t_data *data, int argc, char *argv[])
{
	int	len;

	memset(data, 0, sizeof(t_data));
	if (data_allocate(data, argv) != 0)
	{
		data_free(data);
		return (-1);
	}
	len = ft_atoi(argv[1]);
	rules_init_data(data, argc, argv);
	philos_init_data(data, len);
	return (0);
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
