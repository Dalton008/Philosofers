/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 16:52:59 by mjammie           #+#    #+#             */
/*   Updated: 2021/06/30 15:48:31 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_bonus.h"

void	ft_post_sem(t_all *all)
{
	int	i;

	i = 0;
	waitpid(0, NULL, 0);
	while (i < all->input.num_of_philos)
	{
		sem_post(all->eat_check);
		i++;
	}
}

void	kill_process(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->input.num_of_philos)
	{
		kill(all->pid[i], SIGTERM);
		i++;
	}
	sem_close(all->forks);
	sem_close(all->eat_check);
	sem_close(all->rights_to_write);
	sem_unlink("forks");
	sem_unlink("eat_check");
	sem_unlink("rights_to_write");
}

int	check_death(t_philo	*philo)
{
	if (gettime(philo->params.start) - philo->last_eat > \
		philo->params.time_to_die && philo->stop != 1)
	{
		philo->isdead = 1;
		printstatus(gettime(philo->params.start), "die", philo, \
			"\x1b[31m");
		return (1);
	}
	return (0);
}
