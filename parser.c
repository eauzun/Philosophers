/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:48:38 by emuzun            #+#    #+#             */
/*   Updated: 2025/06/26 19:48:39 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int authenticate_arguments(char *str)
{
	int i;
	i = 0;
	while(ft_isspace(str[i]))
		i++;
	if(str[i] == '+')
		i++;
	if(ft_isdigit(str[i]))
		return 0;
	if(str[i] == '+')
		i++;
	while (str[i])
	{
		if(ft_isdigit(str[i]))
			return (0)
		i++;
	}
	return(1);
}

static void	ft_init_sim(t_sim *sim, char **argv)
{
	sim->num_of_philos = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		sim->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		sim->number_of_times_each_philosopher_must_eat = -1;
	sim->someone_died = 0;
	sim->full_philos = 0;
	pthread_mutex_init(&sim->write_lock, NULL);
	pthread_mutex_init(&sim->dead_lock, NULL);
	pthread_mutex_init(&sim->meal_lock, NULL);
	pthread_mutex_init(&sim->full_lock, NULL);
}

int parse_data(char **argv, t_sim *table)
{
	int i;

	i = 1;
	while(argv[i])
	{
		if(ft_check_argument(argv[i]))
			return(1);
		i++;
	}
	ft_init_sim(table, argv);
	if(table -> nbr_of_philo < 1 || table-> num_of_philos > PHILO_MAX
		|| table->time_to_die <= 0 || table->time_to_eat <= 0
		|| table->time_to_sleep <=0 
	)
		table->start_time = current_milisecond(sim);
}