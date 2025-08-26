#include "../include/philosophers.h"

long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

void	precise_sleep(long ms)
{
	long long	start_time;
	long long	elapsed;
	long long	remaining;

	start_time = get_time_ms();
	while (1)
	{
		elapsed = get_time_ms() - start_time;
		remaining = ms - elapsed;
		if (remaining <= 0)
			break ;
		if (remaining > 10)
			usleep(1000);
		else
			usleep(remaining * 1000);
	}
}

int	ft_atoi(const char *str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}