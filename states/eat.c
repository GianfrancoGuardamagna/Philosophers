/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguardam <gguardam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:17:15 by gguardam          #+#    #+#             */
/*   Updated: 2025/10/06 19:13:10 by gguardam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void is_eating(t_philo *philo)
{
	if(!philo->data->there_is_a_dead_body_on_the_table)
	{
		pthread_mutex_lock(&philo->willpower);
		philo->last_meal_time = get_time();
		philo->meals += 1;
		if(!philo->data->there_is_a_dead_body_on_the_table)
			printf("%ld %d is eating\n", get_timestamp(philo), philo->id);
		pthread_mutex_unlock(&philo->willpower);
		usleep(philo->data->time_to_eat * 1000);
	}
}
