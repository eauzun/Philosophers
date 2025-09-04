#include "philosophers.h"

int	take_forks(t_philo *philo)
{
	if (philo->data->nb_philos == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_unlock(philo->right_fork);
		ft_usleep(philo->data->time_to_die + 1);
		return (ERROR);
	}

	// Even philosophers take left fork first, odd take right first (deadlock prevention)
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
	return (SUCCESS);
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_eat(t_philo *philo)
{
	if (take_forks(philo) == ERROR)
		return ;
		
	print_status(philo, "is eating");
	
	pthread_mutex_lock(&philo->data->data_mutex);
	philo->last_meal_time = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->data_mutex);
	
	ft_usleep(philo->data->time_to_eat);
	put_forks(philo);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	print_status(philo, "is thinking");
	
	// Add small thinking time to prevent busy waiting
	if (philo->data->nb_philos % 2 == 1)
		ft_usleep(1);
}