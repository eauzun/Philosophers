/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:06:08 by emuzun            #+#    #+#             */
/*   Updated: 2025/08/23 16:44:38 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <stdlib.h>

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	int				left_fork;
	int				right_fork;
	long long		last_meal;
	pthread_t		thread;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	int				died;
	int				all_ate;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	writing;
	pthread_mutex_t	meal_check;
	t_philo			*philos;
}	t_data;

// init.c
int			init_all(t_data *data, char **argv);
int			init_mutex(t_data *data);
int			init_philosophers(t_data *data);

// utils.c
int			ft_atoi(const char *str);
void		print_action(t_data *data, int id, char *string);
long long	timestamp(void);
long long	time_diff(long long past, long long pres);
void		smart_sleep(long long time, t_data *data);

// routine.c
void		*p_thread(void *void_philosopher);
void		philo_eats(t_philo *philo);
void		exit_threads(t_data *data, t_philo *philos);

// monitor.c
void		death_checker(t_data *d, t_philo *p);

#endif