#include "../philosophers.h"

int	is_there_a_dead_body_on_the_table(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&philo->data->death_mutex);
	dead = philo->data->there_is_a_dead_body_on_the_table;
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (dead);
}