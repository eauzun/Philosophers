/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 12:00:00 by student           #+#    #+#             */
/*   Updated: 2025/09/04 17:55:37 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*death_monitor(void *arg)
{
	t_philo		*philos;
	int			i;
	long long	time_since_meal;

	philos = (t_philo *)arg;
	precise_sleep(1);
	while (!is_dead(philos->data))
	{
		i = 0;
		while (i < philos->data->nb_philos)
		{
			pthread_mutex_lock(&philos->data->state_lock);
			time_since_meal = get_time_ms() - philos[i].last_meal;
			if (time_since_meal > philos->data->time_to_die)
			{
				philos->data->dead_flag = 1;
				pthread_mutex_unlock(&philos->data->state_lock);
				safe_print(&philos[i], "died");
				return (NULL);
			}
			pthread_mutex_unlock(&philos->data->state_lock);
			i++;
		}
		precise_sleep(1);
	}
	return (NULL);
}

int	start_threads(t_philo *philos, t_data *data)
{
	pthread_t	monitor;
	int			i;

	if (pthread_create(&monitor, NULL, death_monitor, philos) != 0)
		return (ERROR);
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_life, &philos[i]) != 0)
			return (ERROR);
		i++;
	}
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	return (SUCCESS);
}