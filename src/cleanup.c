#include "../include/philosophers.h"

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->philo_count)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
	}
	if (data->philos)
	{
		i = 0;
		while (i < data->philo_count)
		{
			pthread_mutex_destroy(&data->philos[i].meals_mutex);
			i++;
		}
	}
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->start_mutex);
}

void	cleanup_data(t_data *data)
{
	destroy_mutexes(data);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}