/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:08:24 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/15 03:07:28 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>	// pthread_t
# include <stdio.h>		// printf
# include <stdlib.h>	// malloc, free
# include <string.h>	// memset
# include <sys/time.h>	// gettimeofday
# include <unistd.h>	// usleep

typedef unsigned int	t_uint;
typedef pthread_mutex_t	t_mutex;

typedef struct s_rules
{
	t_uint	time_to_die;
	t_uint	time_to_eat;
	t_uint	time_to_sleep;
	t_uint	times_each_must_eat;
	int		simulation_running;
	t_mutex	*mutex;
}	t_rules;

typedef struct s_philo
{
	pthread_t	thread;
	t_uint		id;
	t_rules		*rules;
	t_mutex		*fork_left;
	t_mutex		*fork_right;
	t_uint		times_eaten;
	long		last_meal_time;
	t_mutex		*mutex;
}	t_philo;

typedef struct s_philos
{
	t_uint	len;
	t_philo	*arr;
	t_mutex	*mtx_arr;
}	t_philos;

typedef struct s_forks
{
	t_uint	len;
	t_mutex	*arr;
}	t_forks;

typedef struct s_data
{
	t_rules		rules;
	t_forks		forks;
	t_philos	philos;
	pthread_t	death;
}	t_data;

/* Data */
int		data_malloc(t_data *data, char *argv[]);
void	data_init(t_data *data, int argc, char *argv[]);
void	data_free(t_data *data);
void	data_cleanup(t_data *data);

/* Rules */
void	rules_init(t_data *data, int argc, char *argv[]);
void	rules_free(t_data *data);
void	rules_cleanup(t_data *data);
int		is_simulation_running(t_rules *rules);
void	set_simulation_running(t_rules *rules, int value);

/* Forks */
void	forks_init(t_data *data, t_uint len);
void	forks_free(t_data *data);
void	forks_cleanup(t_data *data);

/* Philos */
void	philos_init(t_data *data, t_uint len);
void	philos_free(t_data *data);
void	philos_cleanup(t_data *data);

/* Actions */
void	philo_think(t_philo *philo);
void	philo_take_forks(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_leave_forks(t_philo *philo);
void	philo_sleep(t_philo *philo);

/* Death */
void	death_init(t_data *data);
void	death_cleanup(t_data *data);

/* Time */
long	timestamp_get(void);

/* Utils */
int		ft_atoi(const char *nptr);

/* Debug */
void	philo_print(t_philo *philo);
void	data_print(t_data *data);
void	print_sizes(t_uint len);

#endif
