#include "philosophers.h"

void *monitor_routine(void *arg)
{
	t_philo	*philos;
	int		n_philos;
	int		all_eaten;
	int		i;
	
	philos = (t_philo *)arg;
	n_philos = philos[0].data->n_philos;
	while (1)
	{
		all_eaten = 1;
		i = 0;
		while (i < n_philos)
		{
			pthread_mutex_lock(&philos[i].willpower);
			if ((get_time() - philos[i].last_meal_time) > philos[i].data->time_to_die)
			{
				philos[i].data->there_is_a_dead_body_on_the_table = 1;
				printf("%ld %d died\n", get_timestamp(&philos[i]), philos[i].id);
				pthread_mutex_unlock(&philos[i].willpower);
				return (NULL);
			}
			if (philos[i].meals < philos[i].data->must_eat_count)
				all_eaten = 0;
			pthread_mutex_unlock(&philos[i].willpower);
			i++;
		}
		if (all_eaten && philos[0].data->must_eat_count != 2147483647)
		{
			philos[0].data->there_is_a_dead_body_on_the_table = 1;
			return (NULL);
		}
		usleep(1000);
	}
	
	return (NULL);
}
