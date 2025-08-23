/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:41:05 by emuzun            #+#    #+#             */
/*   Updated: 2025/08/23 16:41:14 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	check_all_ate(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (data->nb_must_eat != -1 && i < data->nb_philo
		&& philo[i].meals_eaten >= data->nb_must_eat)
		i++;
	if (i == data->nb_philo)
		data->all_ate = 1;
}

void	death_checker(t_data *d, t_philo *p)
{
	int	i;

	d->start_time = timestamp();
	while (!(d->all_ate))
	{
		i = -1;
		while (++i < d->nb_philo && !(d->died))
		{
			pthread_mutex_lock(&(d->meal_check));
			if (time_diff(p[i].last_meal, timestamp()) > d->time_to_die)
			{
				print_action(d, i, "died");
				d->died = 1;
			}
			pthread_mutex_unlock(&(d->meal_check));
			usleep(100);
		}
		if (d->died)
			break ;
		check_all_ate(d, d->philos);
	}
}