/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:08:24 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/29 19:28:15 by dagredan         ###   ########.fr       */
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

typedef pthread_mutex_t	t_mutex;
typedef struct s_data	t_data;

typedef struct s_philo
{
	t_data		*data;
	t_mutex		*mutex;
	pthread_t	thread;
	int			thread_created;
	int			id;
	t_mutex		*fork_left;
	t_mutex		*fork_right;
	int			times_eaten;
	int			is_full;
	long		last_meal_time;
}	t_philo;

typedef struct s_philos
{
	int		len;
	t_philo	*arr;
}	t_philos;

typedef struct s_mutexes
{
	t_mutex	global;
	t_mutex	*forks;
	t_mutex	*philos;
	int		global_initialized;
	int		forks_initialized;
	int		philos_initialized;
}	t_mutexes;

typedef enum e_state
{
	SETUP,
	RUNNING,
	FINISHED
}	t_state;

typedef struct s_rules
{
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		meal_goal;
	t_state	simulation_state;
	long	simulation_start;
}	t_rules;

struct s_data
{
	t_rules		rules;
	t_mutexes	mutexes;
	t_philos	philos;
	pthread_t	death;
	pthread_t	monitor;
	int			death_created;
	int			monitor_created;
};

/* Arguments */
int		arguments_validate(int argc, char *argv[]);

/* Data */
int		data_allocate(t_data *data, char *argv[]);
void	data_init(t_data *data, int argc, char *argv[]);
void	data_free(t_data *data);

/* Rules */
void	rules_init_data(t_data *data, int argc, char *argv[]);
t_state	get_simulation_state(t_data *data);
void	set_simulation_state(t_data *data, t_state value);

/* Mutexes */
int		mutexes_init(t_data *data);
void	mutexes_destroy(t_data *data);

/* Threads */
int		threads_create(t_data *data);
void	threads_join(t_data *data);

/* Philos */
void	philos_init_data(t_data *data, int len);
int		philo_update_last_meal_time(t_philo *philo);
int		philos_create_threads(t_data *data);
void	philos_join_threads(t_data *data);

/* Actions */
int		philo_initial_think(t_philo *philo);
int		philo_think(t_philo *philo);
int		philo_take_forks(t_philo *philo);
int		philo_eat(t_philo *philo);
int		philo_sleep(t_philo *philo);

/* Death */
int		death_create_thread(t_data *data);
void	death_join_thread(t_data *data);

/* Monitor */
int		monitor_create_thread(t_data *data);
void	monitor_join_thread(t_data *data);

/* Time */
long	get_current_time(void);
int		precise_usleep(int usec_goal);

/* Print */
int		print_state_change(t_philo *philo, char *message);

/* Utils */
size_t	ft_strlen(const char *s);
int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
void	print_error(char *message);

/* Debug */
void	philo_print(t_philo *philo);
void	data_print(t_data *data);
void	print_sizes(int len);

#endif
