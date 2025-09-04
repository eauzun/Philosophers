/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 12:00:00 by student           #+#    #+#             */
/*   Updated: 2025/09/04 17:55:37 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parse_args(t_data *data, int argc, char **argv)
{
	data->nb_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat_count = ft_atoi(argv[5]);
	else
		data->must_eat_count = -1;
	data->start_time = get_time_ms();
	data->dead_flag = 0;
	data->forks = NULL;
	return (SUCCESS);
}

static int	init_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->forks)
		return (ERROR);
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (free(data->forks), ERROR);
	if (pthread_mutex_init(&data->state_lock, NULL) != 0)
		return (pthread_mutex_destroy(&data->print_lock), free(data->forks), ERROR);
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

static void	setup_neighbors(t_philo *philos, int nb_philos)
{
	int	i;

	i = 0;
	while (i < nb_philos)
	{
		philos[i].left_neighbor = &philos[(i - 1 + nb_philos) % nb_philos];
		philos[i].right_neighbor = &philos[(i + 1) % nb_philos];
		i++;
	}
}

int	init_simulation(t_data *data, t_philo **philos)
{
	int	i;

	if (init_mutexes(data) == ERROR)
		return (ERROR);
	*philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (!*philos)
		return (ERROR);
	i = 0;
	while (i < data->nb_philos)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].eat_count = 0;
		(*philos)[i].recursion_depth = 0;
		(*philos)[i].last_meal = data->start_time;
		(*philos)[i].data = data;
		i++;
	}
	setup_neighbors(*philos, data->nb_philos);
	return (SUCCESS);
}