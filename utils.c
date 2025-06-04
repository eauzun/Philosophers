#include "philosophers.h"

void	print_status(t_philo *philo, char *status)
{
	long	current_time;

	current_time = get_time();
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!philo->data->simulation_stop)
	{
		printf("%ld %d %s\n", current_time - philo->data->start_time,
			philo->id, status);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	check_simulation_stop(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->stop_mutex);
	stop = data->simulation_stop;
	pthread_mutex_unlock(&data->stop_mutex);
	return (stop);
}

void	set_simulation_stop(t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	data->simulation_stop = 1;
	pthread_mutex_unlock(&data->stop_mutex);
}

int	start_simulation(t_data *data)
{
	int	i;

	if (pthread_create(&data->monitor_thread, NULL, monitor_routine, data) != 0)
		return (1);
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				philosopher_routine, &data->philos[i]) != 0)
		{
			set_simulation_stop(data);
			while (--i >= 0)
				pthread_join(data->philos[i].thread, NULL);
			pthread_join(data->monitor_thread, NULL);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(data->monitor_thread, NULL);
	return (0);
}