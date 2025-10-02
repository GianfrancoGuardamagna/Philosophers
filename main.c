/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguardam <gguardam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:48:18 by gguardam          #+#    #+#             */
/*   Updated: 2025/09/30 17:07:58 by gguardam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//void left_fork(t_philo *philo)
//{
//	pthread_mutex_lock(&philo->fork_left);
//	printf("Philosopher number: %d has the left fork\n", philo->id);
//}

void is_thinking(t_philo *philo)
{
	printf("%ld %d is thinking\n", get_timestamp(philo), philo->id);
}

void is_sleeping(t_philo *philo)
{
	printf("%ld %d is sleeping\n", get_timestamp(philo), philo->id);
	usleep(philo->data->time_to_sleep * 1000);
}

void is_eating(t_philo *philo)
{
	printf("%ld %d is eating\n", get_timestamp(philo), philo->id);
	usleep(philo->data->time_to_eat * 1000);
	philo->last_meal_time = get_time();
}

void *philosopher_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while(1)
	{
		is_thinking(philo);
		
		pthread_mutex_lock(philo->fork_left);
		printf("%ld %d has taken a fork\n", get_timestamp(philo), philo->id);
		pthread_mutex_lock(philo->fork_right);
		printf("%ld %d has taken a fork\n", get_timestamp(philo), philo->id);
		
		is_eating(philo);
		
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		
		is_sleeping(philo);
		
		if (get_time() - philo->last_meal_time >= philo->data->time_to_die)
		{
			printf("%ld %d died\n", get_time() - philo->data->start_time, philo->id);
			break;
		}
	}
	return (NULL);
}

//argv[1] is number of philosophers
void	initialize_philos(t_philo *philos, char **argv)
{
	int	i;
	t_data	data;

	data.n_philos = ft_atoi(argv[1]);
	data.start_time = get_time();
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	data.n_philos = ft_atoi(argv[1]);
	i = 0;
	while(i < ft_atoi(argv[1]))
	{
		philos[i].data = &data;
		philos[i].id = i;
		philos[i].last_meal_time = 0;
		i++;
	}
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		if (pthread_create(&philos[i].thread, NULL, philosopher_routine, &philos[i]) != 0)
		{
			printf("Failed to create thread %d\n", i);
			free(philos);
		}
		i++;
	}
}

//argv[1] is number of philosophers
int	main(int argc, char **argv)
{
	t_philo		*philos;
	int			i;

	if(!check_input(argc, argv))
		return (printf("Invalid Input, expecting INTS:\n{./philo 'number_of_philosophers' 'time_to_die' 'time_to_eat' 'time_to_sleep' [number_of_times_each_philosopher_must_eat]}\n")); //TO DO ERROR MSSG
	philos = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!philos)
		return (printf("Memory allocation failed\n"));
	initialize_philos(philos, argv);
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	free(philos);
	return (0);
}
