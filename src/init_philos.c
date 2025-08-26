#include "../include/philosophers.h"

static void	assign_forks(t_philo *philo, t_data *data, int i)
{
	philo->left_fork = &data->forks[i];
	philo->right_fork = &data->forks[(i + 1) % data->philo_count];
	if (philo->left_fork > philo->right_fork)
	{
		pthread_mutex_t	*temp = philo->left_fork;
		philo->left_fork = philo->right_fork;
		philo->right_fork = temp;
	}
}

static int	init_philosopher(t_philo *philo, t_data *data, int i)
{
	philo->id = i + 1;
	philo->meals_eaten = 0;
	philo->last_meal_time = 0;
	philo->data = data;
	assign_forks(philo, data, i);
	if (pthread_mutex_init(&philo->meals_mutex, NULL))
		return (0);
	return (1);
}

int	init_philosophers(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philos)
		return (0);
	i = 0;
	while (i < data->philo_count)
	{
		if (!init_philosopher(&data->philos[i], data, i))
			return (0);
		i++;
	}
	return (1);
}
