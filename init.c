/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:39:51 by emuzun            #+#    #+#             */
/*   Updated: 2025/08/23 16:42:02 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "philosophers.h"

int	init_mutex(t_data *data)
{
	int	i;

	i = data->nb_philo;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(data->writing), NULL))
		return (1);
	if (pthread_mutex_init(&(data->meal_check), NULL))
		return (1);
	return (0);
}

int	init_philosophers(t_data *data)
{
	int	i;

	i = data->nb_philo;
	while (--i >= 0)
	{
		data->philos[i].id = i;
		data->philos[i].meals_eaten = 0;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->nb_philo;
		data->philos[i].last_meal = 0;
		data->philos[i].data = data;
	}
	return (0);
}

int	init_all(t_data *data, char **argv)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->died = 0;
	data->all_ate = 0;
	if (data->nb_philo < 1 || data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0
		|| data->nb_philo > 250)
		return (1);
	if (argv[5])
	{
		data->nb_must_eat = ft_atoi(argv[5]);
		if (data->nb_must_eat <= 0)
			return (1);
	}
	else
		data->nb_must_eat = -1;
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->philos || !data->forks)
		return (1);
	if (init_mutex(data))
		return (1);
	return (0);
}