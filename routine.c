#include "philosophers.h"

static void i_grabbed_it_first(t_philo *philo)
{
	if(philo->data->there_is_a_dead_body_on_the_table)
		return;
	if (philo->id == philo->data->n_philos)
	{
		pthread_mutex_lock(philo->fork_right);
		if(!philo->data->there_is_a_dead_body_on_the_table)
			printf("%ld %d has taken a fork\n", get_timestamp(philo), philo->id);
		else
			return;
		pthread_mutex_lock(philo->fork_left);
		if(!philo->data->there_is_a_dead_body_on_the_table)
			printf("%ld %d has taken a fork\n", get_timestamp(philo), philo->id);
		else
			return;
	}
	else
	{
		pthread_mutex_lock(philo->fork_left);
		if(!philo->data->there_is_a_dead_body_on_the_table)
			printf("%ld %d has taken a fork\n", get_timestamp(philo), philo->id);
		else
			return;
		pthread_mutex_lock(philo->fork_right);
		if(!philo->data->there_is_a_dead_body_on_the_table)
			printf("%ld %d has taken a fork\n", get_timestamp(philo), philo->id);
		else
			return;
	}
}

static void im_full(t_philo *philo)
{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
}

void *philosopher_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat * 500);
	while (!philo->data->there_is_a_dead_body_on_the_table)
	{
		i_grabbed_it_first(philo);
		if (philo->data->there_is_a_dead_body_on_the_table)
		{
			im_full(philo);
			break;
		}
		is_eating(philo);
		im_full(philo);
		if (philo->data->there_is_a_dead_body_on_the_table)
			break;
		is_sleeping(philo);
		if (philo->data->there_is_a_dead_body_on_the_table)
			break;
		is_thinking(philo);
	}
	
	return (NULL);
}
