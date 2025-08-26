#include "../include/philosophers.h"

int	init_data(t_data *data, int argc, char **argv)
{
	data->philo_count = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->meals_required = ft_atoi(argv[5]);
	else
		data->meals_required = -1;
	data->someone_died = 0;
	data->all_started = 0;
	if (!init_mutexes(data))
		return (0);
	if (!init_forks(data))
		return (0);
	if (!init_philosophers(data))
		return (0);
	return (1);
}

int	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->death_mutex, NULL))
		return (0);
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (0);
	if (pthread_mutex_init(&data->start_mutex, NULL))
		return (0);
	return (1);
}

int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!data->forks)
		return (0);
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (0);
		i++;
	}
	return (1);
}