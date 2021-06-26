/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 18:38:33 by mjammie           #+#    #+#             */
/*   Updated: 2021/06/26 12:28:53 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_bonus.h"

void	take_fork(t_philo *philo)
{
	sem_wait(philo->all->forks);
	printstatus(gettime(philo->params.start), "take left fork", \
		philo, "\x1b[34m");
	// sem_wait(philo->all->forks);
	printstatus(gettime(philo->params.start), "take right fork", \
		philo, "\x1b[34m");
}

void	eat(t_philo *philo)
{
	printstatus(gettime(philo->params.start), "eating", philo, "\x1b[32m");
	ft_usleep(philo->params.time_to_eat);
	philo->last_eat = gettime(philo->params.start);
	// sem_post(philo->all->forks);
	sem_post(philo->all->forks);
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
