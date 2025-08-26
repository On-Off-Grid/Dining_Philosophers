#include "../include/philosophers.h"

static void	init_philo_timing(t_philo *philo)
{
	pthread_mutex_lock(&philo->meals_mutex);
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->meals_mutex);
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
		precise_sleep(philo->data->time_to_die + 1);
		return (NULL);
	}
	while (!check_death(philo->data))
	{
		eat_action(philo);
		if (check_death(philo->data))
			break ;
		sleep_action(philo);
		think_action(philo);
	}
	return (NULL);
}