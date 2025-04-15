/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:31:50 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/15 03:07:19 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	data_malloc(t_data *data, char *argv[])
{
	t_uint	len;

	len = (t_uint)ft_atoi(argv[1]);
	memset(data, 0, sizeof(t_data));
	data->rules.mutex = (t_mutex *)malloc(sizeof(t_mutex));
	if (!data->rules.mutex)
		return (-1);
	data->forks.arr = (t_mutex *)malloc(len * sizeof(t_mutex));
	if (!data->forks.arr)
		return (-1);
	data->philos.arr = (t_philo *)malloc(len * sizeof(t_philo));
	if (!data->philos.arr)
		return (-1);
	data->philos.mtx_arr = (t_mutex *)malloc(len * sizeof(t_mutex));
	if (!data->philos.mtx_arr)
		return (-1);
	return (0);
}

void	data_init(t_data *data, int argc, char *argv[])
{
	t_uint	len;

	len = (t_uint)ft_atoi(argv[1]);
	rules_init(data, argc, argv);
	forks_init(data, len);
	philos_init(data, len);
	death_init(data);
}

void	data_free(t_data *data)
{
	philos_free(data);
	forks_free(data);
	rules_free(data);
}

void	data_cleanup(t_data *data)
{
	death_cleanup(data);
	philos_cleanup(data);
	forks_cleanup(data);
	rules_cleanup(data);
}
