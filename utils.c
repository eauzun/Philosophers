/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:40:23 by emuzun            #+#    #+#             */
/*   Updated: 2025/08/23 16:42:02 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	long int	n;
	int			sign;

	n = 0;
	sign = 1;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			return (-1);
	}
	return ((int)(n * sign));
}

void	print_action(t_data *data, int id, char *string)
{
	pthread_mutex_lock(&(data->writing));
	if (!(data->died))
	{
		printf("%lld ", timestamp() - data->start_time);
		printf("%d ", id + 1);
		printf("%s\n", string);
	}
	pthread_mutex_unlock(&(data->writing));
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void	smart_sleep(long long time, t_data *data)
{
	long long	i;

	i = timestamp();
	while (!(data->died))
	{
		if (time_diff(i, timestamp()) >= time)
			break ;
		usleep(50);
	}
}