/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 11:38:08 by emuzun            #+#    #+#             */
/*   Updated: 2025/09/05 12:31:36 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	error_msg(char *msg)
{
	printf("Error: %s\n", msg);
	return (ERROR);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;

	if (validate_args(argc, argv) == ERROR)
		return (error_msg("Invalid arguments"));
	memset(&data, 0, sizeof(t_data));
	philos = NULL;
	if (init_data(&data, argc, argv) == ERROR)
		return (error_msg("Failed to initialize data"));
	if (init_philos(&philos, &data) == ERROR)
	{
		cleanup_data(&data);
		return (error_msg("Failed to initialize philosophers"));
	}
	if (start_simulation(philos, &data) == ERROR)
	{
		cleanup_philos(philos, &data);
		cleanup_data(&data);
		return (error_msg("Failed to start simulation"));
	}
	cleanup_philos(philos, &data);
	cleanup_data(&data);
	return (SUCCESS);
}
