/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:19:41 by dagredan          #+#    #+#             */
/*   Updated: 2025/04/29 19:28:17 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
		i++;
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

int	philo_handle_state_change(t_philo *philo, char *message)
{
	long	elapsed_time;

	pthread_mutex_lock(&philo->data->mutexes.global);
	if (philo->data->rules.simulation_state != FINISHED)
	{
		elapsed_time = get_current_time() - philo->data->rules.simulation_start;
		if (printf("%ld %d %s\n", elapsed_time, philo->id, message) < 0)
		{
			pthread_mutex_unlock(&philo->data->mutexes.global);
			return (error(philo->data, "printf", "philo_handle_state_change"));
		}
		if (ft_strcmp(message, "died") == 0)
			philo->data->rules.simulation_state = FINISHED;
	}
	pthread_mutex_unlock(&philo->data->mutexes.global);
	return (0);
}
