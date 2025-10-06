#include "philosophers.h"

long get_time(void)
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long get_timestamp(t_philo *philo)
{
	return (get_time() - philo->data.start_time);
}