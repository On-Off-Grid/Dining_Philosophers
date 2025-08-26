#include "../include/philosophers.h"

static int	create_philosopher_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_create(&data->philos[i].thread, NULL, 
				philosopher_routine, &data->philos[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	start_simulation(t_data *data)
{
	pthread_t	monitor_thread;

	data->start_time = get_time_ms();
	set_all_started(data);
	if (pthread_create(&monitor_thread, NULL, monitor_routine, data))
		return (0);
	join_threads(data);
	pthread_join(monitor_thread, NULL);
	return (1);
}

int	run_simulation(t_data *data)
{
	if (!create_philosopher_threads(data))
		return (0);
	if (!start_simulation(data))
		return (0);
	return (1);
}