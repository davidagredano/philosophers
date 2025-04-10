/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:08:24 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/10 11:44:36 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>  // printf
# include <stdlib.h> // malloc, free
# include <string.h> // memset

typedef unsigned int	t_uint;

typedef struct s_rules
{
	t_uint	time_to_die;
	t_uint	time_to_eat;
	t_uint	time_to_sleep;
	t_uint	times_each_must_eat;
}	t_rules;

typedef struct s_philo
{
	t_uint	number;
	t_rules	*rules;
	char	*fork_left;
	char	*fork_right;
	t_uint	times_eaten;
	t_uint	time_of_last_meal;
}	t_philo;

typedef struct s_data
{
	t_rules	rules;
	t_uint	count;
	t_philo	*philosophers;
	char	*forks;
}	t_data;

int		ft_atoi(const char *nptr);

/* Debug */
void	philo_print(t_philo *philo);
void	data_print(t_data *data);

#endif
