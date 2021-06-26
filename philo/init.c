/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 16:38:08 by mjammie           #+#    #+#             */
/*   Updated: 2021/06/20 16:53:38 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	give_forks(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->input.num_of_philos)
	{
		if (i == all->input.num_of_philos - 1)
		{
			all->philosofers[i].left_fork = &all->forks[i];
			all->philosofers[i].right_fork = &all->forks[0];
		}
		else
		{
			all->philosofers[i].left_fork = &all->forks[i];
			all->philosofers[i].right_fork = &all->forks[i + 1];
		}
		i++;
	}
}

void	init_forks(t_all *all)
{
	int	i;

	i = 0;
	all->forks = malloc(sizeof(pthread_mutex_t) * all->input.num_of_philos);
	if (all->forks == 0)
		return ;
	while (i < all->input.num_of_philos)
	{
		pthread_mutex_init(&all->forks[i], NULL);
		i++;
	}
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
	if (all->philosofers == 0)
		return ;
	while (i < num_of_philos)
	{
		all->philosofers[i].stop = 0;
		all->philosofers[i].count_eat = 0;
		all->philosofers[i].isdead = 0;
		all->philosofers[i].all = all;
		all->philosofers[i].last_eat = 0;
		all->philosofers[i].id = i + 1;
		all->philosofers[i].params = all->input;
		i++;
	}
}
