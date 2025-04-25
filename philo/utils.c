/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:10:09 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/25 11:26:27 by dagredan         ###   ########.fr       */
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
