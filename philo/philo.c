/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 16:04:34 by mjammie           #+#    #+#             */
/*   Updated: 2021/06/24 16:59:16 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	check_death(t_all *all, int i)
{
	if (gettime(all->input.start) - all->philosofers[i].last_eat > \
		all->input.time_to_die && all->philosofers[i].stop != 1)
	{
		all->philosofers[i].isdead = 1;
		printstatus(gettime(all->input.start), "die", &all->philosofers[i], \
			"\x1b[31m");
		return (1);
	}
	return (0);
}

void	*check_starvation(void *all)
{
	t_all	*head;
	int		philo_isfull;
	int		i;

	head = (t_all *)all;
	while (1)
	{
		philo_isfull = 0;
		i = 0;
		while (i < head->input.num_of_philos)
		{
			if (head->philosofers[i].count_eat >= head->input.num_of_eat && \
				head->input.num_of_eat != -1)
			{
				philo_isfull++;
				head->philosofers[i].stop = 1;
			}
			if (check_death(all, i))
				return (0);
			i++;
		}
		if (philo_isfull == head->input.num_of_philos)
			return (0);
	}
	return (0);
}

void	*actions(void *philosofers)
{
	t_philo	*head;

	head = (t_philo *)philosofers;
	while (1)
	{
		take_fork(head);
		eat(head);
		head->count_eat++;
		if (head->count_eat == head->params.num_of_eat && \
			head->params.num_of_eat != -1)
		{
			return (0);
		}
		sleeping(head);
		thinking(head);
	}
	return (0);
}

void	ft_philo(t_all *all)
{
	int			i;
	pthread_t	thread_st;

	i = 1;
	pthread_create(&thread_st, NULL, check_starvation, all);
	while (i < all->input.num_of_philos)
	{
		pthread_create(&all->philosofers->thread, NULL, actions, \
			all->philosofers + i);
		i += 2;
	}
	i = 0;
	while (i < all->input.num_of_philos)
	{
		pthread_create(&all->philosofers->thread, NULL, actions, \
			all->philosofers + i);
		i += 2;
	}
	i = -1;
	pthread_join(thread_st, NULL);
	free_all(all);
}

int	main(int argc, char **argv)
{
	t_all	*all;

	all = (struct s_all *)malloc(sizeof(t_all));
	if (all == 0)
		return (0);
	pthread_mutex_init(&all->rights_to_write, NULL);
	if (!init_input(argc, argv, all))
	{
		all->input.start = gettime(0);
		init_philosofers(all->input.num_of_philos, all);
		init_forks(all);
		give_forks(all);
		ft_philo(all);
	}
	else
		return (0);
}
