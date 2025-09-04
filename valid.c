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

int	validate_args(int argc, char **argv)
{
	int	i;
	int	value;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
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
			printf("Error: number_of_times_each_philosopher_must_eat cannot be negative\n");
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

int	is_simulation_over(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->data_mutex);
	result = data->dead_flag || data->finished_eating;
	pthread_mutex_unlock(&data->data_mutex);
	return (result);
}

int	check_philosopher_death(t_philo *philos, t_data *data)
{
	int			i;
	long long	current_time;
	long long	time_since_meal;
	int			all_ate_enough;

	i = 0;
	current_time = get_time();
	all_ate_enough = (data->must_eat_count != -1) ? 1 : 0;
	
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&data->data_mutex);
		time_since_meal = current_time - philos[i].last_meal_time;
		
		if (time_since_meal > data->time_to_die)
		{
			data->dead_flag = 1;
			pthread_mutex_unlock(&data->data_mutex);
			pthread_mutex_lock(&data->print_mutex);
			printf("%lld %d died\n", current_time - data->start_time, philos[i].id);
			pthread_mutex_unlock(&data->print_mutex);
			return (DEAD);
		}
		
		if (data->must_eat_count != -1 && philos[i].eat_count < data->must_eat_count)
			all_ate_enough = 0;
			
		pthread_mutex_unlock(&data->data_mutex);
		i++;
	}
	
	if (all_ate_enough && data->must_eat_count != -1)
	{
		pthread_mutex_lock(&data->data_mutex);
		data->finished_eating = 1;
		pthread_mutex_unlock(&data->data_mutex);
		return (SUCCESS);
	}
	
	return (SUCCESS);
}