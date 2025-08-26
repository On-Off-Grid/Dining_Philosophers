#include "../include/philosophers.h"

int	check_philosopher_death(t_data *data, int i)
{
	long long	current_time;
	long long	last_meal;
	int			time_since_meal;

	current_time = get_time_ms();
	pthread_mutex_lock(&data->philos[i].meals_mutex);
	last_meal = data->philos[i].last_meal_time;
	pthread_mutex_unlock(&data->philos[i].meals_mutex);
	time_since_meal = current_time - last_meal;
	if (time_since_meal >= data->time_to_die)
	{
		set_death(data);
		print_status(&data->philos[i], "died", 1);
		return (1);
	}
	return (0);
}

int	check_all_ate_enough(t_data *data)
{
	int	i;
	int	finished_eating;

	if (data->meals_required <= 0)
		return (0);
	finished_eating = 0;
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&data->philos[i].meals_mutex);
		if (data->philos[i].meals_eaten >= data->meals_required)
			finished_eating++;
		pthread_mutex_unlock(&data->philos[i].meals_mutex);
		i++;
	}
	return (finished_eating == data->philo_count);
}

int	should_stop_simulation(t_data *data)
{
	int	i;

	if (check_death(data))
		return (1);
	if (check_all_ate_enough(data))
		return (1);
	i = 0;
	while (i < data->philo_count)
	{
		if (check_philosopher_death(data, i))
			return (1);
		i++;
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!should_stop_simulation(data))
		precise_sleep(1);
	return (NULL);
}