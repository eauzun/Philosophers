/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:10:57 by emuzun            #+#    #+#             */
/*   Updated: 2025/09/05 13:23:22 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[0] == '+')
		i = 1;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	is_valid_range(int value, int min, int max)
{
	return (value >= min && value <= max);
}

static int	validate_arg_values(int i, int value)
{
	if (i == 1 && !is_valid_range(value, 1, 200))
	{
		printf("Error: number_of_philosophers must be between 1 and 200\n");
		return (ERROR);
	}
	if (i > 1 && i <= 4 && !is_valid_range(value, 60, 2147483647))
	{
		printf("Error: time values must be at least 60ms\n");
		return (ERROR);
	}
	if (i == 6 && value < 0)
	{
		printf("Error: number_of_times_each_philosopher_must_eat");
		printf(" cannot be negative\n");
		return (ERROR);
	}
	return (SUCCESS);
}

int	validate_args(int argc, char **argv)
{
	int	i;
	int	value;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die ", argv[0]);
		printf("time_to_eat time_to_sleep ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		return (ERROR);
	}
	i = 1;
	while (i < argc)
	{
		if (!is_valid_number(argv[i]))
		{
			printf("Error: '%s' is not a valid positive number\n", argv[i]);
			return (ERROR);
		}
		value = ft_atoi(argv[i]);
		if (validate_arg_values(i, value) == ERROR)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}
