/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:40:38 by emuzun            #+#    #+#             */
/*   Updated: 2025/08/23 16:41:42 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_eats(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&(data->forks[philo->left_fork]));
	print_action(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&(data->forks[philo->right_fork]));
	print_action(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&(data->meal_check));
	print_action(data, philo->id, "is eating");
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&(data->meal_check));
	smart_sleep(data->time_to_eat, data);
	(philo->meals_eaten)++;
	pthread_mutex_unlock(&(data->forks[philo->left_fork]));
	pthread_mutex_unlock(&(data->forks[philo->right_fork]));
}

void	*p_thread(void *void_philosopher)
{
	int		i;
	t_philo	*philo;
	t_data	*data;

	i = 0;
	philo = (t_philo *)void_philosopher;
	data = philo->data;
	if (philo->id % 2)
		usleep(15000);
	while (!(data->died))
	{
		philo_eats(philo);
		if (data->all_ate)
			break ;
		print_action(data, philo->id, "is sleeping");
		smart_sleep(data->time_to_sleep, data);
		print_action(data, philo->id, "is thinking");
		i++;
	}
	return (NULL);
}

void	exit_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
		pthread_join(philos[i].thread, NULL);
	i = -1;
	while (++i < data->nb_philo)
		pthread_mutex_destroy(&(data->forks[i]));
	pthread_mutex_destroy(&(data->writing));
	pthread_mutex_destroy(&(data->meal_check));
	free(data->forks);
	free(data->philos);
}