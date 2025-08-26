#include "../include/philosophers.h"

void	print_status(t_philo *philo, char *status, int force)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!check_death(philo->data) || force)
		printf("%lld %d %s\n", get_time_ms() - philo->data->start_time, 
			philo->id, status);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	check_death(t_data *data)
{
	int	is_dead;

	pthread_mutex_lock(&data->death_mutex);
	is_dead = data->someone_died;
	pthread_mutex_unlock(&data->death_mutex);
	return (is_dead);
}

void	set_death(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	data->someone_died = 1;
	pthread_mutex_unlock(&data->death_mutex);
}
