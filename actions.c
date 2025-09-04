/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 12:00:00 by student           #+#    #+#             */
/*   Updated: 2025/09/04 17:55:37 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat_routine(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	if (is_dead(philo->data) || philo->data->nb_philos == 1)
		return ;
	left_fork = (philo->id - 1 + philo->data->nb_philos) % philo->data->nb_philos;
	right_fork = philo->id % philo->data->nb_philos;
	if (recursive_state_check(philo, MAX_RECURSION) > 0)
	{
		pthread_mutex_lock(&philo->data->forks[left_fork]);
		safe_print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[right_fork]);
		safe_print(philo, "has taken a fork");
		safe_print(philo, "is eating");
		pthread_mutex_lock(&philo->data->state_lock);
		philo->last_meal = get_time_ms();
		philo->eat_count++;
		pthread_mutex_unlock(&philo->data->state_lock);
		precise_sleep(philo->data->time_to_eat);
		pthread_mutex_unlock(&philo->data->forks[right_fork]);
		pthread_mutex_unlock(&philo->data->forks[left_fork]);
		recursive_influence_neighbors(philo, 2);
	}
}

void	sleep_and_think(t_philo *philo)
{
	safe_print(philo, "is sleeping");
	precise_sleep(philo->data->time_to_sleep);
	safe_print(philo, "is thinking");
	if (philo->data->nb_philos % 2 == 1)
		precise_sleep(1);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		precise_sleep(1);
	while (!is_dead(philo->data))
	{
		eat_routine(philo);
		if (is_dead(philo->data))
			break ;
		sleep_and_think(philo);
		if (philo->data->must_eat_count != -1 && philo->eat_count >= philo->data->must_eat_count)
			break ;
	}
	return (NULL);
}