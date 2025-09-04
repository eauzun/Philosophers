#include "philosophers.h"

void	destroy_mutexes(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->nb_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
		data->forks = NULL;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->data_mutex);
}

void	cleanup_data(t_data *data)
{
	destroy_mutexes(data);
}

void	cleanup_philos(t_philo *philos, t_data *data)
{
	if (philos)
	{
		free(philos);
		philos = NULL;
	}
	(void)data; // Prevent unused parameter warning
}