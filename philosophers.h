/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 12:00:00 by student           #+#    #+#             */
/*   Updated: 2025/09/04 17:55:53 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define SUCCESS 0
# define ERROR 1
# define MAX_RECURSION 3

typedef struct s_data
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	long long		start_time;
	int				dead_flag;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	state_lock;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	int				recursion_depth;
	long long		last_meal;
	pthread_t		thread;
	t_data			*data;
	struct s_philo	*left_neighbor;
	struct s_philo	*right_neighbor;
}	t_philo;

/* Core Functions */
int			parse_args(t_data *data, int argc, char **argv);
int			init_simulation(t_data *data, t_philo **philos);
int			start_threads(t_philo *philos, t_data *data);
void		cleanup_all(t_data *data, t_philo *philos);

/* Recursive Logic */
int			recursive_state_check(t_philo *philo, int depth);
int			recursive_fork_attempt(t_philo *philo, int depth);
void		recursive_influence_neighbors(t_philo *philo, int depth);

/* Actions */
void		*philo_life(void *arg);
void		*death_monitor(void *arg);
void		eat_routine(t_philo *philo);
void		sleep_and_think(t_philo *philo);

/* Utils */
long long	get_time_ms(void);
void		precise_sleep(long long ms);
void		safe_print(t_philo *philo, char *msg);
int			is_dead(t_data *data);
int			ft_atoi(const char *str);

#endif