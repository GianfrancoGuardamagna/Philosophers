#include "philosophers.h"

static int i_grabbed_it_first(t_philo *philo)
{
	int	dead;

	dead = is_there_a_dead_body_on_the_table(philo);
	if(dead)
		return (0);
	if (philo->id == philo->data->n_philos)
	{
		pthread_mutex_lock(philo->fork_right);
		dead = is_there_a_dead_body_on_the_table(philo);
		if(!dead)
			printf("%ld %d has taken a fork\n", get_timestamp(philo), philo->id);
		else
		{
			pthread_mutex_unlock(philo->fork_right);
			return (0);
		}
		pthread_mutex_lock(philo->fork_left);
		dead = is_there_a_dead_body_on_the_table(philo);
		if(!dead)
			printf("%ld %d has taken a fork\n", get_timestamp(philo), philo->id);
		else
		{
			pthread_mutex_unlock(philo->fork_right);
			pthread_mutex_unlock(philo->fork_left);
			return (0);
		}
	}
	else
	{
		pthread_mutex_lock(philo->fork_left);
		dead = is_there_a_dead_body_on_the_table(philo);
		if(!dead)
			printf("%ld %d has taken a fork\n", get_timestamp(philo), philo->id);
		else
		{
			pthread_mutex_unlock(philo->fork_left);
			return (0);
		}
		pthread_mutex_lock(philo->fork_right);
		dead = is_there_a_dead_body_on_the_table(philo);
		if(!dead)
			printf("%ld %d has taken a fork\n", get_timestamp(philo), philo->id);
		else
		{
			pthread_mutex_unlock(philo->fork_left);
			pthread_mutex_unlock(philo->fork_right);
			return (0);
		}
	}
	return (1);
}

static void im_full(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

static void one_philo_scenario(t_philo *philo)
{
	printf("%ld %d has taken a fork\n", get_timestamp(philo), philo->id);
	usleep(philo->data->time_to_die * 1000);
	return ;
}

void *philosopher_routine(void *arg)
{
	t_philo *philo;
	int		dead;
	int		grabbed;

	philo = (t_philo *)arg;
	dead = is_there_a_dead_body_on_the_table(philo);
	if(philo->data->n_philos == 1)
	{
		one_philo_scenario(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat * 500);
	while (!dead)
	{
		grabbed = i_grabbed_it_first(philo);
		if (!grabbed)
			break;
		dead = is_there_a_dead_body_on_the_table(philo);
		if (dead)
		{
			im_full(philo);
			break;
		}
		is_eating(philo);
		im_full(philo);
		dead = is_there_a_dead_body_on_the_table(philo);
		if (dead)
			break;
		is_sleeping(philo);
		dead = is_there_a_dead_body_on_the_table(philo);
		if (dead)
			break;
		is_thinking(philo);
		dead = is_there_a_dead_body_on_the_table(philo);
	}
	return (NULL);
}
