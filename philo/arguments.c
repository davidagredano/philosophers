/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:01:49 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/29 19:07:59 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	argument_validate(char *arg)
{
	size_t	i;

	i = 0;
	if (arg[0] == '+')
		i++;
	while (arg[i] == '0')
		i++;
	if (ft_strlen(arg + i) < 1 || ft_strlen(arg + i) > 3)
		return (-1);
	while (arg[i] != '\0')
	{
		if (!ft_isdigit(arg[i]))
			return (-1);
		i++;
	}
	return (0);
}

int	arguments_validate(int argc, char *argv[])
{
	int	i;

	if (argc < 5)
	{
		print_error("Too few arguments");
		return (-1);
	}
	else if (argc > 6)
	{
		print_error("Too many arguments");
		return (-1);
	}
	i = 1;
	while (i < argc)
	{
		if (argument_validate(argv[i]) == -1)
		{
			print_error("All arguments must be a positive integer (1-999)");
			return (-1);
		}
		i++;
	}
	return (0);
}
