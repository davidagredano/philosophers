/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:10:09 by dagredan          #+#    #+#             */
/*   Updated: 2025/05/10 14:13:00 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *nptr)
{
	int	accumulated;
	int	i;

	i = 0;
	if (nptr[i] == '+')
		i++;
	accumulated = 0;
	while (ft_isdigit(nptr[i]))
	{
		accumulated = accumulated * 10 + (nptr[i] - '0');
		i++;
	}
	return (accumulated);
}

void	print_error(char *message)
{
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 1);
}

int	error(t_data *data, char *syscall, char *func)
{
	pthread_mutex_lock(&data->mutexes.global);
	if (data->rules.simulation_state != FINISHED)
	{
		data->rules.simulation_state = FINISHED;
		write(STDERR_FILENO, "Error: ", 7);
		write(STDERR_FILENO, syscall, ft_strlen(syscall));
		write(STDERR_FILENO, " failed in ", 11);
		write(STDERR_FILENO, func, ft_strlen(func));
		write(STDERR_FILENO, "\n", 1);
	}
	pthread_mutex_unlock(&data->mutexes.global);
	return (-1);
}
