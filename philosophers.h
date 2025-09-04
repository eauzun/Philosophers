#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

# define SUCCESS 0
# define ERROR 1
# define DEAD 2

typedef struct s_data
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				finished_eating;
	long long		start_time;
	int				dead_flag;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	data_mutex;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long long		last_meal_time;
	pthread_t		thread;
	t_data			*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

/* Utils */
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
int			ft_strlen(const char *str);
long long	get_time(void);
void		ft_usleep(long long milliseconds);
void		print_status(t_philo *philo, char *status);

/* Init */
int			init_data(t_data *data, int argc, char **argv);
int			init_philos(t_philo **philos, t_data *data);
int			init_mutexes(t_data *data);

/* Threads */
void		*philo_routine(void *arg);
void		*monitor_routine(void *arg);
int			start_simulation(t_philo *philos, t_data *data);

/* Actions */
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);
int			take_forks(t_philo *philo);
void		put_forks(t_philo *philo);

/* Cleanup */
void		cleanup_data(t_data *data);
void		cleanup_philos(t_philo *philos, t_data *data);
void		destroy_mutexes(t_data *data);

/* Validation */
int			validate_args(int argc, char **argv);
int			is_simulation_over(t_data *data);
int			check_philosopher_death(t_philo *philos, t_data *data);

#endif