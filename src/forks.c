#include "../include/philosophers.h"

static int	try_acquire_first_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (check_death(philo->data))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	print_status(philo, "has taken a fork", 0);
	return (1);
}

static int	try_acquire_second_fork(t_philo *philo)
{
	if (philo->data->philo_count == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	pthread_mutex_lock(philo->right_fork);
	if (check_death(philo->data))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	print_status(philo, "has taken a fork", 0);
	return (1);
}

int	acquire_forks(t_philo *philo)
{
	if (!try_acquire_first_fork(philo))
		return (0);
	if (!try_acquire_second_fork(philo))
		return (0);
	return (1);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}
