/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguardam <gguardam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:18:45 by gguardam          #+#    #+#             */
/*   Updated: 2025/10/21 18:40:23 by gguardam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	is_thinking(t_philo *philo)
{
	long	think_time;

	if (!is_there_a_dead_body_on_the_table(philo))
	{
		pthread_mutex_lock(&philo->willpower);
		if (!is_there_a_dead_body_on_the_table(philo))
			printf("%ld %d is thinking\n", get_timestamp(philo), philo->id);
		pthread_mutex_unlock(&philo->willpower);
		if (philo->data->n_philos % 2 != 0)
		{
			think_time = (philo->data->time_to_eat * 2 \
- philo->data->time_to_sleep);
			if (think_time < 0)
				think_time = 0;
			usleep(think_time * 1000);
		}
	}
}
