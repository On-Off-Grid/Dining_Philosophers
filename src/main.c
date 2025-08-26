#include "../include/philosophers.h"

static int	validate_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s philo_count time_to_die time_to_eat ", argv[0]);
		printf("time_to_sleep [meals_required]\n");
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) <= 0)
		{
			printf("Error: All arguments must be positive integers\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!validate_args(argc, argv))
		return (1);
	memset(&data, 0, sizeof(t_data));
	if (!init_data(&data, argc, argv))
	{
		cleanup_data(&data);
		return (1);
	}
	if (!run_simulation(&data))
	{
		cleanup_data(&data);
		return (1);
	}
	cleanup_data(&data);
	return (0);
}