#include "philosophers.h"

static int	check_death(t_data *data)
{
	int		i;
	long	current_time;
	long	last_meal;

	i = 0;
	current_time = get_time();
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		last_meal = data->philos[i].last_meal_time;
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		if (current_time - last_meal > data->time_to_die)
		{
			pthread_mutex_lock(&data->print_mutex);
			if (!data->simulation_stop)
			{
				printf("%ld %d %s\n", current_time - data->start_time,
					data->philos[i].id, DIED_MSG);
				set_simulation_stop(data);
			}
			pthread_mutex_unlock(&data->print_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_eat_count(t_data *data)
{
	int	i;
	int	finished_eating;

	if (data->must_eat_count == -1)
		return (0);
	i = 0;
	finished_eating = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		if (data->philos[i].eat_count >= data->must_eat_count)
			finished_eating++;
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		i++;
	}
	if (finished_eating == data->philo_count)
	{
		set_simulation_stop(data);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!check_simulation_stop(data))
	{
		if (check_death(data) || check_eat_count(data))
			break ;
		usleep(1000);
	}
	return (NULL);
}