#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (parse_args(argc, argv, &data) != 0)
	{
		printf("Error: Invalid arguments\n");
		printf("Usage: ./philo number_of_philosophers time_to_die ");
		printf("time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	if (init_data(&data) != 0)
	{
		printf("Error: Initialization failed\n");
		cleanup_data(&data);
		return (1);
	}
	if (start_simulation(&data) != 0)
	{
		printf("Error: Simulation failed\n");
		cleanup_data(&data);
		return (1);
	}
	cleanup_data(&data);
	return (0);
}