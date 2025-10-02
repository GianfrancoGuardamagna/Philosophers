#ifndef PHILOSOPHERS_H
#	define PHILOSOPHERS_H

#include <stdio.h> //printf
#include <stdlib.h> //malloc and free
#include <bits/pthreadtypes.h> //pthread_t 
#include <pthread.h> //pthread_create, pthread_join
#include <unistd.h> //usleep
#include <sys/time.h> //gettimeofday

typedef struct s_data
{
	int				n_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
} t_data;

typedef struct s_philo
{
	int				id;
	long			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	t_data			*data;
} t_philo;


/*Utils*/
int	ft_isint(char *str);
int	ft_atoi(const char *str);

/*Parser*/
int	check_input(int argc, char **argv);

/*Time*/
long get_time(void);
long get_timestamp(t_philo *philo);

#endif