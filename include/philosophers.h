#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meals_mutex;
	pthread_t		thread;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	int				someone_died;
	int				all_started;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	start_mutex;
	t_philo			*philos;
}	t_data;

/* Core functions */
int			main(int argc, char **argv);
int			run_simulation(t_data *data);

/* Initialization functions */
int			init_data(t_data *data, int argc, char **argv);
int			init_mutexes(t_data *data);
int			init_philosophers(t_data *data);
int			init_forks(t_data *data);

/* Thread functions */
void		*philosopher_routine(void *arg);
void		*monitor_routine(void *arg);
int			acquire_forks(t_philo *philo);
void		release_forks(t_philo *philo);

/* Action functions */
void		eat_action(t_philo *philo);
void		sleep_action(t_philo *philo);
void		think_action(t_philo *philo);
void		stagger_start(t_philo *philo);

/* Monitor functions */
int			check_philosopher_death(t_data *data, int i);
int			check_all_ate_enough(t_data *data);
int			should_stop_simulation(t_data *data);

/* Utility functions */
long long	get_time_ms(void);
void		precise_sleep(long ms);
int			ft_atoi(const char *str);

/* Status functions */
void		print_status(t_philo *philo, char *status, int force);
int			check_death(t_data *data);
void		set_death(t_data *data);

/* Synchronization functions */
int			check_all_started(t_data *data);
void		set_all_started(t_data *data);
void		wait_for_start(t_data *data);

/* Cleanup functions */
void		cleanup_data(t_data *data);
void		destroy_mutexes(t_data *data);
void		join_threads(t_data *data);

#endif