#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

# define FORK_MSG "has taken a fork"
# define EAT_MSG "is eating"
# define SLEEP_MSG "is sleeping"
# define THINK_MSG "is thinking"
# define DIED_MSG "died"

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_mutex;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				philo_count;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat_count;
	long			start_time;
	int				simulation_stop;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	stop_mutex;
	t_philo			*philos;
	pthread_t		monitor_thread;
}	t_data;

// Parsing and validation
int		parse_args(int argc, char **argv, t_data *data);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);

// Time utilities
long	get_time(void);
void	ft_usleep(long time);

// Initialization
int		init_data(t_data *data);
int		init_philos(t_data *data);
int		init_mutexes(t_data *data);

// Simulation
void	*philosopher_routine(void *arg);
void	*monitor_routine(void *arg);
int		start_simulation(t_data *data);

// Actions
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);

// Utilities
void	print_status(t_philo *philo, char *status);
int		check_simulation_stop(t_data *data);
void	set_simulation_stop(t_data *data);

// Cleanup
void	cleanup_data(t_data *data);
void	destroy_mutexes(t_data *data);

#endif