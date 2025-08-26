#include "../include/philosophers.h"

int	check_all_started(t_data *data)
{
	int	started;

	pthread_mutex_lock(&data->start_mutex);
	started = data->all_started;
	pthread_mutex_unlock(&data->start_mutex);
	return (started);
}

void	set_all_started(t_data *data)
{
	pthread_mutex_lock(&data->start_mutex);
	data->all_started = 1;
	pthread_mutex_unlock(&data->start_mutex);
}

void	wait_for_start(t_data *data)
{
	while (!check_all_started(data))
		precise_sleep(1);
}
