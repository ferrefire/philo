/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   locks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/20 20:51:26 by ferre         #+#    #+#                 */
/*   Updated: 2024/06/20 22:35:01 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philo *philo, int state, long time)
{
	char *print_state;

	if (state < 0 || state > 4)
		return;
	pthread_mutex_lock(philo->print_lock);
	if (state < 3)
	{
		if (state == THINKING)
			print_state = "thinking";
		else if (state == EATING)
			print_state = "eating";
		else if (state == SLEEPING)
			print_state = "sleeping";
		printf("%ld %d is %s\n", time / 1000, philo->philo_id, print_state);
	}
	else if (state == DEAD)
		printf("%ld %d died\n", time / 1000, philo->philo_id);
	else if (state == FORK)
		printf("%ld %d has taken a fork\n", total_time() / 1000, philo->philo_id);
	pthread_mutex_unlock(philo->print_lock);
}

void	old_print_state(t_philo *philo, long time)
{
	char	*print_state;

	if (philo->state < 0 || philo->state > 3)
		return ; 
	pthread_mutex_lock(philo->print_lock);
	if (philo->state == THINKING)
		print_state = "thinking";
	else if (philo->state == EATING)
		print_state = "eating";
	else if (philo->state == SLEEPING)
		print_state = "sleeping";
	printf("%ld %d is %s\n", time / 1000, philo->philo_id, print_state);
	pthread_mutex_unlock(philo->print_lock);
}

int check_state(t_philo *philo, int state)
{
	int	result;

	pthread_mutex_lock(&(philo->philo_lock));
	result = philo->state == state;
	pthread_mutex_unlock(&(philo->philo_lock));

	return (result);
}

void	change_state(t_philo *philo, int state, long time)
{
	if (is_dead(philo))
		return ;
	pthread_mutex_lock(&(philo->philo_lock));
	philo->state = state;
	if (philo->state == EATING)
		philo->last_eaten_at = time;
	print_state(philo, state, time);
	pthread_mutex_unlock(&(philo->philo_lock));
}

int	is_dead(t_philo *philo)
{
	long	time;
	int		state;

	pthread_mutex_lock(&(philo->philo_lock));
	state = 0;
	time = total_time();
	if (philo->philo_dead)
		state = 1;
	else if (philo->time_to_die < time - philo->last_eaten_at)
	{
		philo->philo_dead = 1;
		print_state(philo, DEAD, time);
		state = 1;
	}
	pthread_mutex_unlock(&(philo->philo_lock));
	return (state);
}
