/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguardam <gguardam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:48:18 by gguardam          #+#    #+#             */
/*   Updated: 2025/09/30 17:07:58 by gguardam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	check_input(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	if(argc == 4 || argc == 5)
	{
		while(argv[i])
		{
			if(!ft_isint(ft_atoi(argv[i])))
				return(0);
			i++;
		}
		return(1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	if(!check_input(argc, argv))
		return (printf("Error Input")); //TO DO ERROR MSSG
	return (0);
}
