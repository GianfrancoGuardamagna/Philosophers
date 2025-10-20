/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguardam <gguardam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:48:18 by gguardam          #+#    #+#             */
/*   Updated: 2025/10/20 14:00:00 by gguardam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	cleanup(t_philo *philos, t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&philos[i].willpower);
		i++;
	}
	pthread_mutex_destroy(&data->death_mutex);
	free(forks);
	free(data);
	free(philos);
}

static int	init_monitor(pthread_t *monitor, t_philo *philos)
{
	if (pthread_create(monitor, NULL, monitor_routine, philos) != 0)
	{
		printf("Failed to create monitor thread\n");
		return (0);
	}
	return (1);
}

static int	init_philos(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, \
philosopher_routine, &philos[i]) != 0)
		{
			printf("Failed to create thread %d\n", i);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	join_threads(t_philo *philos, pthread_t monitor, int n_philos)
{
	int	i;

	pthread_join(monitor, NULL);
	i = 0;
	while (i < n_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo			*philos;
	t_data			*data;
	pthread_t		monitor;
	pthread_mutex_t	*forks;

	if (!check_input(argc, argv))
		return (printf(INVALID_INPUT), 1);
	data = data_loader(argv, argc);
	if (!data)
		return (1);
	forks = fork_loader(data);
	if (!forks)
		return (free(data), 1);
	philos = philos_loader(data, forks);
	if (!philos)
		return (free(forks), free(data), 1);
	if (!init_monitor(&monitor, philos))
		return (cleanup(philos, data, forks), 1);
	if (!init_philos(data, philos))
		return (cleanup(philos, data, forks), 1);
	join_threads(philos, monitor, data->n_philos);
	cleanup(philos, data, forks);
	return (0);
}
