/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguardam <gguardam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:48:18 by gguardam          #+#    #+#             */
/*   Updated: 2025/10/20 13:20:34 by gguardam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h> //printf
# include <stdlib.h> //malloc and free
# include <bits/pthreadtypes.h> //pthread_t 
# include <pthread.h> //pthread_create, pthread_join
# include <unistd.h> //usleep
# include <sys/time.h> //gettimeofday

# define INVALID_INPUT "Invalid input, \
expecting INTS:\n{./philo 'number_of_philosophers' 'time_to_die' 'time_to_eat' \
'time_to_sleep' [number_of_times_each_philosopher_must_eat]}\n"
# define MEMORY_ALLOCATION_ERROR "Memory allocation failed\n"
# define FORK_ERROR "Error while allocating mutex\n"

typedef struct s_data
{
	int				n_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat_count;
	long			start_time;
	int				there_is_a_dead_body_on_the_table;
	pthread_mutex_t	death_mutex;
}	t_data;

typedef struct s_philo
{
	int				id;
	long			last_meal_time;
	long			meals;
	pthread_t		thread;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	willpower;
	t_data			*data;
}	t_philo;

/*Routine*/
void			*philosopher_routine(void *arg);

/*Monitor*/
void			*monitor_routine(void *arg);

/*Utils*/
int				ft_isint(char *str);
int				ft_atoi(const char *str);
int				is_there_a_dead_body_on_the_table(t_philo *philo);

/*Loader*/
pthread_mutex_t	*fork_loader(t_data *data);
t_data			*data_loader(char **argv, int argc);
t_philo			*philos_loader(t_data *data, pthread_mutex_t *forks);

/*Parser*/
int				check_input(int argc, char **argv);

/*Time*/
long			get_time(void);
long			get_timestamp(t_philo *philo);

/*States*/
void			is_eating(t_philo *philo);
void			is_thinking(t_philo *philo);
void			is_sleeping(t_philo *philo);

#endif