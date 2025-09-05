/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_situations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:27:30 by emuzun            #+#    #+#             */
/*   Updated: 2025/09/05 13:32:46 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_simulation_over(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->data_mutex);
	result = data->dead_flag || data->finished_eating;
	pthread_mutex_unlock(&data->data_mutex);
	return (result);
}

static int	check_single_philo(t_philo *philo, t_data *data,
		long long current_time, int *all_ate_enough)
{
	long long	time_since_meal;

	pthread_mutex_lock(&data->data_mutex);
	time_since_meal = current_time - philo->last_meal_time;
	if (time_since_meal > data->time_to_die)
	{
		data->dead_flag = 1;
		pthread_mutex_unlock(&data->data_mutex);
		pthread_mutex_lock(&data->print_mutex);
		printf("%lld %d died\n", current_time - data->start_time, philo->id);
		pthread_mutex_unlock(&data->print_mutex);
		return (DEAD);
	}
	if (data->must_eat_count != -1 && philo->eat_count < data->must_eat_count)
		*all_ate_enough = 0;
	pthread_mutex_unlock(&data->data_mutex);
	return (SUCCESS);
}

int	check_philosopher_death(t_philo *philos, t_data *data)
{
	int			i;
	long long	current_time;
	int			all_ate_enough;

	i = 0;
	current_time = get_time();
	all_ate_enough = 1;
	if (data->must_eat_count == -1)
		all_ate_enough = 0;
	while (i < data->nb_philos)
	{
		if (check_single_philo(&philos[i], data,
				current_time, &all_ate_enough) == DEAD)
			return (DEAD);
		i++;
	}
	if (all_ate_enough && data->must_eat_count != -1)
	{
		pthread_mutex_lock(&data->data_mutex);
		data->finished_eating = 1;
		pthread_mutex_unlock(&data->data_mutex);
	}
	return (SUCCESS);
}
