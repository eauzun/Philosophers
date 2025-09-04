/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 12:00:00 by student           #+#    #+#             */
/*   Updated: 2025/09/04 17:55:37 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	recursive_state_check(t_philo *philo, int depth)
{
	long long	time_since_meal;

	if (depth <= 0 || depth > MAX_RECURSION || is_dead(philo->data))
		return (philo->recursion_depth);
	philo->recursion_depth = depth;
	pthread_mutex_lock(&philo->data->state_lock);
	time_since_meal = get_time_ms() - philo->last_meal;
	pthread_mutex_unlock(&philo->data->state_lock);
	if (time_since_meal > philo->data->time_to_die / depth)
		return (depth);
	if (depth > 1)
	{
		if (recursive_state_check(philo->left_neighbor, depth - 1) > 1)
			return (depth);
		if (recursive_state_check(philo->right_neighbor, depth - 1) > 1)
			return (depth);
	}
	return (0);
}

int	recursive_fork_attempt(t_philo *philo, int depth)
{
	int	left_fork;
	int	right_fork;

	if (depth <= 0 || is_dead(philo->data))
		return (0);
	if (philo->data->nb_philos == 1)
		return (0);
	left_fork = (philo->id - 1 + philo->data->nb_philos) % philo->data->nb_philos;
	right_fork = philo->id % philo->data->nb_philos;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[left_fork]);
		safe_print(philo, "has taken a fork");
		if (depth > 1 && recursive_fork_attempt(philo->right_neighbor, depth - 1))
		{
			pthread_mutex_lock(&philo->data->forks[right_fork]);
			safe_print(philo, "has taken a fork");
			return (1);
		}
		pthread_mutex_unlock(&philo->data->forks[left_fork]);
	}
	return (0);
}

void	recursive_influence_neighbors(t_philo *philo, int depth)
{
	if (depth <= 0 || depth > MAX_RECURSION || is_dead(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->state_lock);
	philo->left_neighbor->recursion_depth = depth - 1;
	philo->right_neighbor->recursion_depth = depth - 1;
	pthread_mutex_unlock(&philo->data->state_lock);
	if (depth > 1)
	{
		recursive_influence_neighbors(philo->left_neighbor, depth - 1);
		recursive_influence_neighbors(philo->right_neighbor, depth - 1);
	}
}