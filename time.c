#include "philosophers.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long time)
{
	long	start;
	long	current;

	start = get_time();
	while (1)
	{
		current = get_time();
		if (current - start >= time)
			break;
		usleep(500);
	}
}