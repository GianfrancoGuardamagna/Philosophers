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

void	is_thinking(t_philo *philo)
{
	if (!is_there_a_dead_body_on_the_table(philo))
	{
		pthread_mutex_lock(&philo->willpower);
		if (!is_there_a_dead_body_on_the_table(philo))
			printf("%ld %d is thinking\n", get_timestamp(philo), philo->id);
		pthread_mutex_unlock(&philo->willpower);
	}
}
