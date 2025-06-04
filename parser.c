#include "philosophers.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

static int	is_valid_number(const char *str)
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

static int	validate_args(t_data *data)
{
	if (data->philo_count <= 0 || data->philo_count > 200)
		return (1);
	if (data->time_to_die <= 0)
		return (1);
	if (data->time_to_eat <= 0)
		return (1);
	if (data->time_to_sleep <= 0)
		return (1);
	if (data->must_eat_count < -1)
		return (1);
	return (0);
}

int	parse_args(int argc, char **argv, t_data *data)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (1);
	i = 1;
	while (i < argc)
	{
		if (!is_valid_number(argv[i]))
			return (1);
		i++;
	}
	data->philo_count = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->must_eat_count = -1;
	if (argc == 6)
		data->must_eat_count = ft_atoi(argv[5]);
	return (validate_args(data));
}