/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguardam <gguardam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:18:57 by gguardam          #+#    #+#             */
/*   Updated: 2025/10/14 13:10:43 by gguardam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_input(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc == 5 || argc == 6)
	{
		if (ft_atoi(argv[1]) <= 0)
			return (0);
		while (argv[i])
		{
			if (!ft_isint(argv[i]))
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}
