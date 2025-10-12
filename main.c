/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguardam <gguardam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:48:18 by gguardam          #+#    #+#             */
/*   Updated: 2025/10/06 19:12:30 by gguardam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void my_job_was_done(t_philo *philos, t_data *data, pthread_mutex_t	*forks)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&philos[i].willpower);
		i++;
	}
	free(forks);
	free(data);
	free(philos);
}

int	main(int argc, char **argv)
{
	t_philo			*philos;
	t_data			*data;
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	int				i;

	if(!check_input(argc, argv))
		return (printf(invalid_input));
	data = data_loader(argv, argc);
	forks = fork_loader(data);
	philos = philos_loader(data, forks);
	if (pthread_create(&monitor, NULL, monitor_routine, philos) != 0)
	{
		printf("Failed to create monitor thread\n");
		free(philos);
		exit(1);
	}
	i = 0;
	while(i < data->n_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, philosopher_routine, &philos[i]) != 0)
		{
			printf("Failed to create thread %d\n", i);
			free(philos);
			exit(1);
		}
		i++;
	}
	pthread_join(monitor, NULL);
	i = 0;
	while (i < data->n_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	my_job_was_done(philos, data, forks);
	return (0);
}
