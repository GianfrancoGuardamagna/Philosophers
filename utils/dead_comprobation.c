/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_comprobation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguardam <gguardam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:18:57 by gguardam          #+#    #+#             */
/*   Updated: 2025/10/14 13:10:43 by gguardam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	is_there_a_dead_body_on_the_table(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&philo->data->death_mutex);
	dead = philo->data->there_is_a_dead_body_on_the_table;
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (dead);
}
