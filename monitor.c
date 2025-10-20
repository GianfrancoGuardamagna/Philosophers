/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguardam <gguardam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:48:18 by gguardam          #+#    #+#             */
/*   Updated: 2025/10/20 13:20:34 by gguardam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	announce_death(t_philo *philos, int i)
{
	pthread_mutex_lock(&philos[i].data->death_mutex);
	philos[i].data->there_is_a_dead_body_on_the_table = 1;
	pthread_mutex_unlock(&philos[i].data->death_mutex);
	printf("%ld %d died\n", get_timestamp(&philos[i]), philos[i].id);
	return (0);
}

static int	check_if_dead(t_philo *philos, int i)
{
	long	time_since_meal;

	pthread_mutex_lock(&philos[i].willpower);
	time_since_meal = get_time() - philos[i].last_meal_time;
	if (time_since_meal > philos[i].data->time_to_die)
	{
		announce_death(philos, i);
		pthread_mutex_unlock(&philos[i].willpower);
		return (0);
	}
	pthread_mutex_unlock(&philos[i].willpower);
	return (1);
}

static int	check_meals_completed(t_philo *philos, int n_philos)
{
	int	i;
	int	all_eaten;

	if (philos[0].data->must_eat_count == 2147483647)
		return (0);
	all_eaten = 1;
	i = 0;
	while (i < n_philos)
	{
		pthread_mutex_lock(&philos[i].willpower);
		if (philos[i].meals < philos[i].data->must_eat_count)
			all_eaten = 0;
		pthread_mutex_unlock(&philos[i].willpower);
		i++;
	}
	return (all_eaten);
}

static int	stop_simulation(t_philo *philos)
{
	pthread_mutex_lock(&philos[0].data->death_mutex);
	philos[0].data->there_is_a_dead_body_on_the_table = 1;
	pthread_mutex_unlock(&philos[0].data->death_mutex);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	int		n_philos;
	int		i;

	philos = (t_philo *)arg;
	n_philos = philos[0].data->n_philos;
	while (1)
	{
		i = 0;
		while (i < n_philos)
		{
			if (!check_if_dead(philos, i))
				return (NULL);
			i++;
		}
		if (check_meals_completed(philos, n_philos))
			return (stop_simulation(philos), NULL);
		usleep(100);
	}
	return (NULL);
}
