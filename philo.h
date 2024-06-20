/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/23 15:06:30 by ferre         #+#    #+#                 */
/*   Updated: 2024/06/20 22:36:18 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# define EATING 0
# define SLEEPING 1
# define THINKING 2
# define DEAD 3
# define FORK 4

typedef struct philo
{
	pthread_t		thread_id;
	pthread_mutex_t philo_fork;
	pthread_mutex_t philo_lock;
	pthread_mutex_t *print_lock;
	int				philo_dead;
	int				philo_id;
	int				state;
	int				philo_count;
	int				must_eat_times;
	long			last_eaten_at;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	void			**philo_list;
}				t_philo;
long			total_time(void);
long			ft_atoi(char *str);
void			change_state(t_philo *philo, int state, long time);
int				is_dead(t_philo *philo);
int				check_args(int argc, char **argv);
int				check_state(t_philo *philo, int state);
void			print_state(t_philo *philo, int state, long time);

#endif
