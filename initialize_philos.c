#include "philosophers.h"

static t_data	data_loader(char **argv, int argc)
{
	t_data	data;

	data.n_philos = ft_atoi(argv[1]);
	data.start_time = get_time();
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	data.must_eat_count = -1;

	if (argc == 6)
		data.must_eat_count = atoi(argv[5]);
	return (data);
}

void	initialize_philos(t_philo *philos, char **argv, int argc)
{
	int	i;
	t_data	data;

	data = data_loader(argv, argc);
	i = 0;
	while(i < ft_atoi(argv[1]))
	{
		philos[i].data = data;
		philos[i].id = i + 1;
		philos[i].last_meal_time = 0;
		philos[i].meals = 0;
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
