/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/25 22:59:19 by ferre         #+#    #+#                 */
/*   Updated: 2024/05/27 17:25:40 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	total_time(void)
{
	struct timeval	timev;

	gettimeofday(&timev, NULL);
	return (timev.tv_sec * 1000000 + timev.tv_usec);
}

long	ft_atoi(char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i])
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result);
}

void	change_state(t_philo *philo, int state, long time)
{
	char	*print_state;

	if (is_dead(philo))
		return ;
	philo->state = state;
	if (philo->state == THINKING)
		print_state = "thinking";
	else if (philo->state == EATING)
		print_state = "eating";
	else if (philo->state == SLEEPING)
		print_state = "sleeping";
	else
		return ;
	printf("%ld %d is %s\n", time / 1000, philo->philo_id, print_state);
}

int	is_dead(t_philo *philo)
{
	long	time;

	time = total_time();
	if (philo->state == DEAD || philo->philo_dead)
		return (1);
	else if (philo->time_to_die < time - philo->last_eaten_at)
	{
		philo->philo_dead = 1;
		philo->state = DEAD;
		printf("%ld %d died\n", time / 1000, philo->philo_id);
		return (1);
	}
	return (0);
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
		exit(EXIT_FAILURE);
	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if ((j == 0 && argv[i][j] == 48) || argv[i][j] < 48 ||
				argv[i][j] > 57)
				exit(EXIT_FAILURE);
		}
	}
	return (1);
}
