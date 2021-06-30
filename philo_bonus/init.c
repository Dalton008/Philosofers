/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:37:22 by mjammie           #+#    #+#             */
/*   Updated: 2021/06/30 14:39:03 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_bonus.h"

int	init_sem(t_all *all)
{
	all->pid = malloc(sizeof(pid_t) * all->input.num_of_philos);
	sem_unlink("forks");
	sem_unlink("rights_to_write");
	sem_unlink("eat_check");
	all->forks = sem_open("forks", O_CREAT, S_IRWXU, \
		(all->input.num_of_philos));
	all->rights_to_write = sem_open("rights_to_write", O_CREAT, S_IRWXU, 1);
	all->eat_check = sem_open("eat_check", O_CREAT, S_IRWXU, 0);
	if (all->forks <= 0 || all->rights_to_write <= 0)
		return (1);
	return (0);
}

int	init_input(int argc, char **argv, t_all *all)
{
	if (!check_argv(argc, argv))
	{
		all->input.num_of_philos = ft_atoi(argv[1]);
		all->input.time_to_die = ft_atoi(argv[2]);
		all->input.time_to_eat = ft_atoi(argv[3]);
		all->input.time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			all->input.num_of_eat = ft_atoi(argv[5]);
		else
			all->input.num_of_eat = -1;
	}
	else
	{
		printf("Invalid input\n");
		return (1);
	}
	return (0);
}

void	init_philosofers(int num_of_philos, t_all *all)
{
	int		i;

	i = 0;
	all->philosofers = (struct s_philo *)malloc(sizeof(t_philo) * \
		all->input.num_of_philos);
	while (i < num_of_philos)
	{
		all->philosofers[i].count_eat = 0;
		all->philosofers[i].all = all;
		all->philosofers[i].last_eat = 0;
		all->philosofers[i].id = i + 1;
		all->philosofers[i].params = all->input;
		i++;
	}
}
