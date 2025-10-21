/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguardam <gguardam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:48:18 by gguardam          #+#    #+#             */
/*   Updated: 2025/10/21 18:20:37 by gguardam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	i_grabbed_it_first(t_philo *philo)
{
	if (is_there_a_dead_body_on_the_table(philo))
		return (0);
	pthread_mutex_lock(philo->fork_right);
	if (is_there_a_dead_body_on_the_table(philo))
	{
		pthread_mutex_unlock(philo->fork_right);
		return (0);
	}
	printf("%ld %d has taken a fork\n", \
get_timestamp(philo), philo->id);
	pthread_mutex_lock(philo->fork_left);
	if (is_there_a_dead_body_on_the_table(philo))
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return (0);
	}
	printf("%ld %d has taken a fork\n", \
get_timestamp(philo), philo->id);
	return (1);
}

static void	im_full(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

static void	philo_cycle(t_philo *philo)
{
	int	dead;
	int	grabbed;

	dead = is_there_a_dead_body_on_the_table(philo);
	while (!dead)
	{
		grabbed = i_grabbed_it_first(philo);
		if (!grabbed)
			break ;
		is_eating(philo);
		im_full(philo);
		if (is_there_a_dead_body_on_the_table(philo))
			break ;
		is_sleeping(philo);
		if (is_there_a_dead_body_on_the_table(philo))
			break ;
		is_thinking(philo);
		dead = is_there_a_dead_body_on_the_table(philo);
	}
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->n_philos == 1)
	{
		printf("%ld %d has taken a fork\n", get_timestamp(philo), philo->id);
		usleep(philo->data->time_to_die * 1000);
		return (0);
	}
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat * 500);
	philo_cycle(philo);
	return (NULL);
}
