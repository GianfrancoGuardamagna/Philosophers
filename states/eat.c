/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguardam <gguardam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:17:15 by gguardam          #+#    #+#             */
/*   Updated: 2025/10/14 13:10:08 by gguardam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void is_eating(t_philo *philo)
{
	int dead;

	dead = is_there_a_dead_body_on_the_table(philo);
	if(!dead)
	{
		pthread_mutex_lock(&philo->willpower);
		philo->last_meal_time = get_time();
		philo->meals += 1;
		dead = is_there_a_dead_body_on_the_table(philo);
		if(!dead)
			printf("%ld %d is eating\n", get_timestamp(philo), philo->id);
		pthread_mutex_unlock(&philo->willpower);
		usleep(philo->data->time_to_eat * 1000);
	}
}
