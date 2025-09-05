/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:10:37 by emuzun            #+#    #+#             */
/*   Updated: 2025/09/05 13:21:22 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_data(t_data *data, int argc, char **argv)
{
	data->nb_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat_count = ft_atoi(argv[5]);
	else
		data->must_eat_count = -1;
	data->finished_eating = 0;
	data->start_time = get_time();
	data->dead_flag = 0;
	data->forks = NULL;
	return (init_mutexes(data));
}

static int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			free(data->forks);
			pthread_mutex_destroy(&data->print_mutex);
			pthread_mutex_destroy(&data->data_mutex);
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

int	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (ERROR);
	if (pthread_mutex_init(&data->data_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_mutex);
		return (ERROR);
	}
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->forks)
	{
		pthread_mutex_destroy(&data->print_mutex);
		pthread_mutex_destroy(&data->data_mutex);
		return (ERROR);
	}
	if (init_forks(data) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

static void	assign_forks(t_philo *philo, t_data *data, int i)
{
	if (i == 0)
	{
		philo->left_fork = &data->forks[data->nb_philos - 1];
		philo->right_fork = &data->forks[0];
	}
	else
	{
		philo->left_fork = &data->forks[i - 1];
		philo->right_fork = &data->forks[i];
	}
}

int	init_philos(t_philo **philos, t_data *data)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (!*philos)
		return (ERROR);
	i = 0;
	while (i < data->nb_philos)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].eat_count = 0;
		(*philos)[i].last_meal_time = data->start_time;
		(*philos)[i].data = data;
		assign_forks(&(*philos)[i], data, i);
		i++;
	}
	return (SUCCESS);
}
