/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguardam <gguardam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:18:45 by gguardam          #+#    #+#             */
/*   Updated: 2025/10/14 13:11:21 by gguardam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void is_thinking(t_philo *philo)
{
	int dead;

	dead = is_there_a_dead_body_on_the_table(philo);
	if(!dead)
	{
		pthread_mutex_lock(&philo->willpower);
		dead = is_there_a_dead_body_on_the_table(philo);
		if(!dead)
			printf("%ld %d is thinking\n", get_timestamp(philo), philo->id);
		pthread_mutex_unlock(&philo->willpower);
	}
}
