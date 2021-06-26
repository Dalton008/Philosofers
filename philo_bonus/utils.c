/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:38:45 by mjammie           #+#    #+#             */
/*   Updated: 2021/06/24 19:22:49 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_bonus.h"

int	check_argv(int argc, char **argv)
{
	int	n;
	int	i;

	i = 1;
	if (argc < 5)
		return (1);
	while (i < argc)
	{
		n = 0;
		while (argv[i][n])
		{
			if (argv[i][n] >= 48 && argv[i][n] <= 57)
				n++;
			else
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int	minus;
	int	num_count;
	int	result;

	minus = 1;
	result = 0;
	num_count = 19;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		minus = minus * -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= 48 && *str <= 57)
	{
		if (!num_count--)
			return ((1 + minus) / (-2));
		result = result * 10 + *str - 48;
		str++;
	}
	return (result * minus);
}

long	gettime(long start)
{
	struct timeval	tv;
	long			mls;

	gettimeofday(&tv, NULL);
	mls = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (mls - start);
}

void	ft_usleep(int in)
{
	time_t	start;
	time_t	end;

	start = gettime(0);
	end = gettime(0) + in;
	while (start < end)
	{
		usleep(10);
		start = gettime(0);
	}
}

void	printstatus(long time, char *message, t_philo *philo, char *color)
{
	sem_wait(philo->all->rights_to_write);
	printf("%s%ld Philosofer %d %s\n", color, time, philo->id, message);
	if (!philo->isdead)
		sem_post(philo->all->rights_to_write);
}
