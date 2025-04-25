/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:08:24 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/25 10:23:45 by dagredan         ###   ########.fr       */
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

# define SPINLOCK_THRESHOLD_USEC 1000

typedef unsigned int	t_uint;
typedef pthread_mutex_t	t_mutex;
typedef struct s_data	t_data;

typedef struct s_philo
{
	t_data		*data;
	t_mutex		*mutex;
	pthread_t	thread;
	t_uint		id;
	t_mutex		*fork_left;
	t_mutex		*fork_right;
	t_uint		times_eaten;
	int			is_full;
	long		last_meal_time;
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

typedef struct s_rules
{
	t_uint	time_to_die;
	t_uint	time_to_eat;
	t_uint	time_to_sleep;
	t_uint	meal_goal;
	int		simulation_running;
	long	simulation_start;
}	t_rules;

typedef struct s_mutexes
{
	t_mutex	*rules;
	t_mutex	*print;
}	t_mutexes;

struct s_data
{
	t_mutexes	mutexes;
	t_rules		rules;
	t_forks		forks;
	t_philos	philos;
	pthread_t	death;
	pthread_t	monitor;
};

/* Data */
int		data_malloc(t_data *data, char *argv[]);
void	data_init(t_data *data, int argc, char *argv[]);
void	data_free(t_data *data);
void	data_cleanup(t_data *data);

/* Mutexes */
void	mutexes_init(t_data *data);
void	mutexes_free(t_data *data);
void	mutexes_cleanup(t_data *data);

/* Rules */
void	rules_init(t_data *data, int argc, char *argv[]);
int		is_simulation_running(t_data *data);
void	set_simulation_running(t_data *data, int value);

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

/* Monitor */
void	monitor_init(t_data *data);
void	monitor_cleanup(t_data *data);

/* Time */
long	get_current_time(void);
int		precise_usleep(t_uint usec_goal);

/* Print */
void	print_state_change(t_philo *philo, char *message);

/* Utils */
size_t	ft_strlen(const char *s);
int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
void	print_error(char *message);

/* Debug */
void	philo_print(t_philo *philo);
void	data_print(t_data *data);
void	print_sizes(t_uint len);

#endif
