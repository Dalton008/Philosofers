/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 18:14:14 by mjammie           #+#    #+#             */
/*   Updated: 2021/06/30 12:23:10 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	printstatus(gettime(philo->params.start), "take left fork", \
		philo, "\x1b[34m");
	pthread_mutex_lock(philo->right_fork);
	printstatus(gettime(philo->params.start), "take right fork", \
		philo, "\x1b[34m");
}

void	eat(t_philo *philo)
{
	printstatus(gettime(philo->params.start), "eating", philo, "\x1b[32m");
	philo->last_eat = gettime(philo->params.start);
	ft_usleep(philo->params.time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	printstatus(gettime(philo->params.start), "sleeping", philo, "\x1b[36m");
	ft_usleep(philo->params.time_to_sleep);
}

void	thinking(t_philo *philo)
{
	printstatus(gettime(philo->params.start), "thinking", philo, "\x1b[35m");
}
