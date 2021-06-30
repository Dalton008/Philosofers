/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:28:50 by mjammie           #+#    #+#             */
/*   Updated: 2021/06/30 15:49:47 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_bonus.h"

void	*check_count_eat(void *all)
{
	int		i;
	t_all	*head;

	i = 0;
	head = (t_all *)all;
	while (i < head->input.num_of_philos)
	{
		sem_wait(head->eat_check);
		i++;
	}
	i = 0;
	while (i < head->input.num_of_philos)
	{
		kill(head->pid[i], SIGTERM);
		i++;
	}
	sem_unlink("forks");
	sem_unlink("rights_to_write");
	sem_unlink("eat_check");
	exit(0);
	return (0);
}

void	*check_starvation(void *philo)
{
	t_philo	*head;
	int		i;
	int		check;

	i = 0;
	head = (t_philo *)philo;
	check = 1;
	while (1)
	{
		if (check_death(head))
		{
			exit (0);
		}
		if (check && head->params.num_of_eat != -1 && head->count_eat >= \
			head->params.num_of_eat)
		{
			sem_post(head->all->eat_check);
			check = 0;
		}
		usleep(1000);
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
		sleeping(philo);
		thinking(philo);
	}
}

void	ft_philo(t_all *all)
{
	int			i;
	pthread_t	thread_st;

	i = 0;
	if (all->input.num_of_eat != -1)
		pthread_create(&thread_st, NULL, check_count_eat, all);
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
	ft_post_sem(all);
	pthread_join(thread_st, NULL);
	kill_process(all);
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
