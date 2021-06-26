/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:28:50 by mjammie           #+#    #+#             */
/*   Updated: 2021/06/24 19:29:00 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_bonus.h"

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

void	*check_starvation(void *philo)
{
	t_philo	*head;
	int		philo_isfull;
	int		i;

	i = 0;
	head = (t_philo *)philo;
	while (1)
	{
		philo_isfull = 0;
		if (head->count_eat >= head->params.num_of_eat && \
				head->params.num_of_eat != -1)
		{
			philo_isfull++;
		}
		if (check_death(head))
		{
			exit (0);
		}
		if (philo_isfull == head->params.num_of_philos)
		{
			exit (0);
		}
	}
	return (0);
}

void	actions(t_philo *philo)
{
	while (1)
	{
		take_fork(philo);
		eat(philo);
		philo->count_eat++;
		if (philo->count_eat == philo->params.num_of_eat && \
			philo->params.num_of_eat != -1)
		{
			return ;
		}
		sleeping(philo);
		thinking(philo);
	}
}

void	ft_philo(t_all *all)
{
	int			i;
	pthread_t	thread_st;

	i = 0;
	while (i < all->input.num_of_philos)
	{
		all->pid[i] = fork();
		if (all->pid[i] == 0)
		{
			pthread_create(&thread_st, NULL, check_starvation, \
				&all->philosofers[i]);
			actions(&all->philosofers[i]);
			i = all->input.num_of_philos;
		}
		i++;
	}
	kill_process(all);
	sem_close(all->forks);
	sem_close(all->rights_to_write);
	sem_unlink("forks");
	sem_unlink("rights_to_write");
	exit(0);
}

int	main(int argc, char **argv)
{
	t_all	*all;

	all = (struct s_all *)malloc(sizeof(t_all));
	if (!init_input(argc, argv, all))
	{
		all->isfull = 0;
		all->dead = 0;
		all->input.start = gettime(0);
		init_philosofers(all->input.num_of_philos, all);
		if (init_sem(all))
			return (0);
		ft_philo(all);
		exit (0);
	}
	else
		return (0);
}
