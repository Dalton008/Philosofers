/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 16:52:59 by mjammie           #+#    #+#             */
/*   Updated: 2021/06/24 19:30:22 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_bonus.h"

void	kill_process(t_all *all)
{
	int	i;
	int	j;
	int	status;

	i = 0;
	j = 0;
	while (i < all->input.num_of_philos)
	{
		waitpid(0, &status, 0);
		if (status == 0)
		{
			j = 0;
			while (j < all->input.num_of_philos)
			{
				kill(all->pid[j], SIGTERM);
				j++;
			}
		}
		i++;
	}
}
