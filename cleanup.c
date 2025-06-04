#include "philosophers.h"

void	destroy_mutexes(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->philo_count)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
		data->forks = NULL;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
}

void	cleanup_data(t_data *data)
{
	int	i;

	if (data->philos)
	{
		i = 0;
		while (i < data->philo_count)
		{
			pthread_mutex_destroy(&data->philos[i].meal_mutex);
			i++;
		}
		free(data->philos);
		data->philos = NULL;
	}
	destroy_mutexes(data);
}