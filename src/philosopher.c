#include "../include/philosophers.h"

static void	init_philo_timing(t_philo *philo)
{
	pthread_mutex_lock(&philo->meals_mutex);
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->meals_mutex);
}

static void	single_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork", 0);
	precise_sleep(philo->data->time_to_die + 1);
	pthread_mutex_unlock(philo->left_fork);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_for_start(philo->data);
	init_philo_timing(philo);
	stagger_start(philo);
	if (philo->data->philo_count == 1)
	{
		single_philo_routine(philo);
		return (NULL);
	}
	while (!should_stop_simulation(philo->data))
	{
		eat_action(philo);
		if (should_stop_simulation(philo->data))
			break ;
		sleep_action(philo);
		think_action(philo);
	}
	return (NULL);
}