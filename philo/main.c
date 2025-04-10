/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:08:15 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/10 11:42:42 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arguments_validate(int argc)
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
	if (arguments_validate(argc) != 0)
		return (EXIT_FAILURE);
	printf("number_of_philosophers: %s\n", argv[1]);
	printf("time_to_die: %s\n", argv[2]);
	printf("time_to_eat: %s\n", argv[3]);
	printf("time_to_sleep: %s\n", argv[4]);
	if (argc == 6)
		printf("times_each_must_eat: %s\n", argv[5]);
}
