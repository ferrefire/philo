/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/23 15:01:23 by ferre         #+#    #+#                 */
/*   Updated: 2024/06/20 22:44:13 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat(t_philo *philo, t_philo **philo_list, int right_fork)
{
	pthread_mutex_lock(&philo->philo_fork);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(&philo->philo_fork);
		return (0);
	}
	print_state(philo, FORK, total_time());
	pthread_mutex_lock(&philo_list[right_fork]->philo_fork);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(&philo->philo_fork);
		pthread_mutex_unlock(&philo_list[right_fork]->philo_fork);
		return (0);
	}
	print_state(philo, FORK, total_time());
	change_state(philo, EATING, total_time());
	usleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->philo_fork);
	pthread_mutex_unlock(&philo_list[right_fork]->philo_fork);
	pthread_mutex_lock(&(philo->philo_lock));
	if (philo->must_eat_times > 0)
		philo->must_eat_times--;
	pthread_mutex_unlock(&(philo->philo_lock));
	return (1);
}

void	*threadf(void *arg)
{
	t_philo	*philo;
	t_philo	**philo_list;
	int		right_fork;

	philo = arg;
	philo_list = (t_philo **)philo->philo_list;
	philo->philo_dead = 0;
	philo->state = THINKING;
	philo->last_eaten_at = total_time();
	right_fork = philo->philo_id;
	if (right_fork == philo->philo_count)
		right_fork = 0;
	while (!is_dead(philo) && philo->philo_count > 1)
	{
		if (check_state(philo, THINKING))
			eat(philo, philo_list, right_fork);
		else if (check_state(philo, EATING))
		{
			change_state(philo, SLEEPING, total_time());
			usleep(philo->time_to_sleep);
		}
		else if (check_state(philo, SLEEPING))
			change_state(philo, THINKING, total_time());
	}
	pthread_exit(NULL);
}

void	setup(char **argv, int argc, pthread_mutex_t *print_lock, t_philo **philos)
{
	int	i;

	i = -1;
	while (++i < ft_atoi(argv[1]))
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i] || pthread_mutex_init(&(philos[i]->philo_fork), NULL)
			|| pthread_mutex_init(&(philos[i]->philo_lock), NULL))
			exit(EXIT_FAILURE);
		philos[i]->print_lock = print_lock;
		philos[i]->philo_id = i + 1;
		philos[i]->philo_count = ft_atoi(argv[1]);
		philos[i]->time_to_die = ft_atoi(argv[2]) * 1000;
		philos[i]->time_to_eat = ft_atoi(argv[3]) * 1000;
		philos[i]->time_to_sleep = ft_atoi(argv[4]) * 1000;
		philos[i]->last_eaten_at = total_time();
		philos[i]->must_eat_times = -1;
		if (argc == 6)
			philos[i]->must_eat_times = ft_atoi(argv[5]);
		philos[i]->philo_list = (void **)philos;
	}
	i = -1;
	while (usleep(100) == 0 && ++i < ft_atoi(argv[1]))
		if (pthread_create(&(philos[i]->thread_id), NULL, threadf, philos[i]))
			exit(EXIT_FAILURE);
}

void	philosophize(t_philo **philos, int count, int argc)
{
	int	i;
	int	total_meals;

	i = -1;
	total_meals = -1;
	if (argc == 6)
		total_meals = 0;
	while (1)
	{
		if (++i >= count)
		{
			i = 0;
			if (total_meals == 0)
				break ;
			else if (argc == 6)
				total_meals = 0;
		}
		if (is_dead(philos[i]))
			break ;
		pthread_mutex_lock(&(philos[i]->philo_lock));
		total_meals += philos[i]->must_eat_times;
		pthread_mutex_unlock(&(philos[i]->philo_lock));
	}
}

int	main(int argc, char **argv)
{
	t_philo			**philos;
	pthread_mutex_t	print_lock;
	int				i;

	check_args(argc, argv);
	philos = malloc(sizeof(void *) * ft_atoi(argv[1]));
	if (!philos)
		exit(EXIT_FAILURE);
	if (pthread_mutex_init(&print_lock, NULL))
		exit(EXIT_FAILURE);
	setup(argv, argc, &print_lock, philos);
	philosophize(philos, ft_atoi(argv[1]), argc);
	i = -1;
	while (++i < ft_atoi(argv[1]))
	{
		pthread_mutex_lock(&(philos[i]->philo_lock));
		philos[i]->philo_dead = 1;
		pthread_mutex_unlock(&(philos[i]->philo_lock));
	}
	usleep(1000);
	while (--i >= 0)
		pthread_join(philos[i]->thread_id, NULL);
	while (++i < ft_atoi(argv[1]))
	{
		pthread_mutex_destroy(&(philos[i]->philo_fork));
		pthread_mutex_destroy(&(philos[i]->philo_lock));
		free(philos[i]);
	}
	free(philos);
	pthread_mutex_destroy(&print_lock);
	pthread_exit(NULL);
}
