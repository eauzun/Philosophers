/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:48:42 by emuzun            #+#    #+#             */
/*   Updated: 2025/06/26 19:48:43 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define  PHILOSOPHERS_H

#include <limits.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include<unistd.h>

#define PHILO_MAX 200

# define COLOR_RED "\033[31m"
# define COLOR_GREEN "\033[32m"
# define COLOR_YELLOW "\033[33m"
# define COLOR_BLUE "\033[34m"
# define COLOR_MAGENTA "\033[35m"
# define COLOR_CYAN "\033[36m"
# define COLOR_WHITE "\033[37m"
# define COLOR_RESET "\033[0m"

#endif


int	ft_isspace(char c);
int	ft_is_digit(char c);
int	ft_atoi(const char *str);
int parse_data(char **argv, t_sim *table);


typedef struct s_philosophers
{
	size_t id;
	size_t eaten_meals;
	int eating;
	size_t last_meal;
	pthread_t	thread;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right fork;
	t_simulator	*sim;
	pthread_mutex_t	mutex;

}t_philosophers;

typedef struct s_simulator
{
	int philo_count;
	int time_to_die;
	int time_to_sleep;
	int time_to_eat;
	int	eat_count;
	int	full_philosophers;
	int	is_anyone_dead;
	size_t	start_time;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		full_lock;
	pthread_mutex_t		*forks;
	t_philosophers				*philos;
	struct timeval		begin_time;
}t_simulator;

