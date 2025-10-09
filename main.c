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

void *philosopher_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if(philo->data.n_philos == 1)
		one_philo(philo);
	else if(philo->data.n_philos == 2)
		return (NULL);
	else if(philo->data.n_philos == 3)
		return (NULL);
	else if(philo->data.n_philos > 3)
		return (NULL);
	// while(1)
	// {
	// 	is_thinking(philo);
		
	// 	pthread_mutex_lock(philo->fork_left);
	// 	printf("%ld %d has taken a fork\n", get_timestamp(philo), philo->id);
	// 	pthread_mutex_lock(philo->fork_right);
	// 	printf("%ld %d has taken a fork\n", get_timestamp(philo), philo->id);
		
	// 	is_eating(philo);
		
	// 	pthread_mutex_unlock(philo->fork_left);
	// 	pthread_mutex_unlock(philo->fork_right);
		
	// 	is_sleeping(philo);
		
	// 	if (get_time() - philo->last_meal_time >= philo->data->time_to_die)
	// 	{
	// 		printf("%ld %d died\n", get_time() - philo->data->start_time, philo->id);
	// 		break;
	// 	}
	// }
	return (NULL);
}

//argv[1] is number of philosophers
int	main(int argc, char **argv)
{
	t_philo		*philos;
	int			i;

	if(!check_input(argc, argv))
		return (printf(invalid_input));
	philos = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!philos)
		return (printf(memory_allocation_error));
	initialize_philos(philos, argv, argc);
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	free(philos);
	return (0);
}
