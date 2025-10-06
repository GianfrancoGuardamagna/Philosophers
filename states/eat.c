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
	printf("%ld %d is eating\n", get_timestamp(philo), philo->id);
	usleep(philo->data.time_to_eat * 1000);
	philo->last_meal_time = get_time();
}
