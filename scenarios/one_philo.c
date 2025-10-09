#include "philosophers.h"

void one_philo(t_philo *philo)
{
	while((philo->last_meal_time - get_timestamp(philo)) < philo->data.time_to_die) //Deberia controlarlo el monitor
	{
		if(philo->data.must_eat_count != -1 && philo->meals >= philo->data.must_eat_count)
		{
			printf("%ld %d ate %d times\n", get_timestamp(philo), philo->id, philo->data.must_eat_count);
			exit(0);
		}
		is_eating(philo);
		is_sleeping(philo);
		is_thinking(philo);
	}
	is_dead(philo);
}
