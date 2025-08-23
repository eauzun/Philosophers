/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:44:02 by emuzun            #+#    #+#             */
/*   Updated: 2025/08/23 16:44:16 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"

int	error_manager(int error)
{
	if (error == 1)
		printf("Wrong amount of arguments\n");
	if (error == 2)
		printf("Invalid arguments\n");
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (argc != 5 && argc != 6)
		return (error_manager(1));
	if (init_all(&data, argv))
		return (error_manager(2));
	if (init_philosophers(&data))
		return (error_manager(2));
	i = -1;
	while (++i < data.nb_philo)
	{
		if (pthread_create(&(data.philos[i].thread), NULL,
				p_thread, &(data.philos[i])))
			return (1);
		data.philos[i].last_meal = timestamp();
	}
	death_checker(&data, data.philos);
	exit_threads(&data, data.philos);
	return (0);
}