#include "philosophers.h"

t_data	*data_loader(char **argv, int argc)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->n_philos = ft_atoi(argv[1]);
	data->start_time = get_time();
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->must_eat_count = 2147483647;
	data->there_is_a_dead_body_on_the_table = 0;

	if (argc == 6)
		data->must_eat_count = atoi(argv[5]);
	return (data);
}

pthread_mutex_t	*fork_loader(t_data *data)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!forks)
	{
		printf(fork_error);
		exit(1);
	}
	i = 0;
	while(i < data->n_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

t_philo	*philos_loader(t_data *data, pthread_mutex_t	*forks)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * data->n_philos);
	if (!philos)
	{
		printf(memory_allocation_error);
		return (NULL);
	}
	i = 0;
	while(i < data->n_philos)
	{
		philos[i].data = data;
		philos[i].id = i + 1;
		philos[i].last_meal_time = data->start_time;
		philos[i].meals = 0;
		philos[i].fork_left = &forks[i];
		philos[i].fork_right = &forks[(i + 1) % data->n_philos];
		pthread_mutex_init(&philos[i].willpower, NULL);
		i++;
	}
	return (philos);
}
