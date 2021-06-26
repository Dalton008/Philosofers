/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:17:56 by mjammie           #+#    #+#             */
/*   Updated: 2021/06/24 17:00:09 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	free_all(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->input.num_of_philos)
		pthread_mutex_destroy(&all->forks[i]);
	free(all->forks);
	free(all->philosofers);
	pthread_mutex_destroy(&all->rights_to_write);
}
