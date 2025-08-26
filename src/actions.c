#include "../include/philosophers.h"

void	eat_action(t_philo *philo)
{
	if (!acquire_forks(philo))
		return ;
	pthread_mutex_lock(&philo->meals_mutex);
	philo->last_meal_time = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_mutex);
	print_status(philo, "is eating", 0);
	precise_sleep(philo->data->time_to_eat);
	release_forks(philo);
}

void	sleep_action(t_philo *philo)
{
	print_status(philo, "is sleeping", 0);
	precise_sleep(philo->data->time_to_sleep);
}

void	think_action(t_philo *philo)
{
	print_status(philo, "is thinking", 0);
	if (philo->data->philo_count % 2 && philo->data->time_to_eat > 10)
		precise_sleep(philo->data->time_to_eat / 10);
}

void	stagger_start(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->philo_count > 1)
	{
		if (philo->id % 2)
			precise_sleep(1);
		else if (data->time_to_eat > 10)
			precise_sleep(data->time_to_eat / 10);
	}
}
