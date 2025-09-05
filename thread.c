/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:10:28 by emuzun            #+#    #+#             */
/*   Updated: 2025/09/05 13:18:21 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#include "philosophers.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(200);
	while (!is_simulation_over(philo->data))
	{
		philo_eat(philo);
		if (is_simulation_over(philo->data))
			break ;
		philo_sleep(philo);
		if (is_simulation_over(philo->data))
			break ;
		philo_think(philo);
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	ft_usleep(200);
	while (!is_simulation_over(philos->data))
	{
		if (check_philosopher_death(philos, philos->data) == DEAD)
			break ;
		ft_usleep(200);
	}
	return (NULL);
}

static int	create_threads(t_philo *philos, t_data *data, pthread_t *monitor)
{
	int	i;

	if (pthread_create(monitor, NULL, monitor_routine, philos) != 0)
		return (ERROR);
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_create(&philos[i].thread, NULL,
				philo_routine, &philos[i]) != 0)
		{
			pthread_mutex_lock(&data->data_mutex);
			data->dead_flag = 1;
			pthread_mutex_unlock(&data->data_mutex);
			while (--i >= 0)
				pthread_join(philos[i].thread, NULL);
			pthread_join(*monitor, NULL);
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

static void	join_threads(t_philo *philos, t_data *data, pthread_t monitor)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
}

int	start_simulation(t_philo *philos, t_data *data)
{
	pthread_t	monitor;

	if (create_threads(philos, data, &monitor) == ERROR)
		return (ERROR);
	join_threads(philos, data, monitor);
	return (SUCCESS);
}
