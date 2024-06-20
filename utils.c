/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/25 22:59:19 by ferre         #+#    #+#                 */
/*   Updated: 2024/06/20 20:54:04 by ferre         ########   odam.nl         */
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
