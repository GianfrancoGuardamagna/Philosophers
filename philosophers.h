#ifndef PHILOSOPHERS_H
#	define PHILOSOPHERS_H

#include <stdio.h> //printf
#include <stdlib.h> //malloc and free
#include <bits/pthreadtypes.h> //pthread_t 
#include <pthread.h> //pthread_create, pthread_join
#include <unistd.h> //usleep
#include <sys/time.h> //gettimeofday

#define invalid_input "Invalid Input, expecting INTS:\n{./philo 'number_of_philosophers' 'time_to_die' 'time_to_eat' 'time_to_sleep' [number_of_times_each_philosopher_must_eat]}\n"
#define memory_allocation_error "Memory allocation failed\n"

typedef struct s_data
{
	int				n_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat_count;
	long			start_time;
} t_data;

typedef struct s_philo
{
	int				id;
	long			last_meal_time;
	long			meals;
	pthread_t		thread;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	t_data			data;
} t_philo;


/*Main*/
void *philosopher_routine(void *arg);

/*Utils*/
int	ft_isint(char *str);
int	ft_atoi(const char *str);

/*Initialize Philos*/
void	initialize_philos(t_philo *philos, char **argv, int argc);

/*Parser*/
int	check_input(int argc, char **argv);

/*Time*/
long get_time(void);
long get_timestamp(t_philo *philo);

/*States*/
void is_eating(t_philo *philo);
void is_thinking(t_philo *philo);
void is_sleeping(t_philo *philo);
void is_dead(t_philo *philo);

/*Scenarios*/
void one_philo(t_philo *philo);

#endif