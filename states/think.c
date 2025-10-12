/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguardam <gguardam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:18:45 by gguardam          #+#    #+#             */
/*   Updated: 2025/10/06 17:18:45 by gguardam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void is_thinking(t_philo *philo)
{
	if(!philo->data->there_is_a_dead_body_on_the_table)
	{
		pthread_mutex_lock(&philo->willpower);
		if(!philo->data->there_is_a_dead_body_on_the_table)
			printf("%ld %d is thinking\n", get_timestamp(philo), philo->id);
		pthread_mutex_unlock(&philo->willpower);
	}
}
