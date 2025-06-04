#include "philosophers.h"

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, FORK_MSG);
		if (philo->data->philo_count == 1)
		{
			ft_usleep(philo->data->time_to_die + 1);
			pthread_mutex_unlock(philo->right_fork);
			return ;
		}
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, FORK_MSG);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, FORK_MSG);
		if (philo->data->philo_count == 1)
		{
			ft_usleep(philo->data->time_to_die + 1);
			pthread_mutex_unlock(philo->left_fork);
			return ;
		}
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, FORK_MSG);
	}
}

static void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_eat(t_philo *philo)
{
	take_forks(philo);
	if (philo->data->philo_count == 1)
		return ;
	print_status(philo, EAT_MSG);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->meal_mutex);
	ft_usleep(philo->data->time_to_eat);
	release_forks(philo);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, SLEEP_MSG);
	ft_usleep(philo->data->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	print_status(philo, THINK_MSG);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2);
	while (!check_simulation_stop(philo->data))
	{
		philo_eat(philo);
		if (check_simulation_stop(philo->data))
			break ;
		philo_sleep(philo);
		if (check_simulation_stop(philo->data))
			break ;
		philo_think(philo);
	}
	return (NULL);
}