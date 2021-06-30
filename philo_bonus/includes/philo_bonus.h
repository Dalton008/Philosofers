/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:29:48 by mjammie           #+#    #+#             */
/*   Updated: 2021/06/30 15:48:46 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_all	t_all;

typedef struct s_input
{
	int				num_of_philos;
	int				time_to_die;
	long			time_to_eat;
	int				time_to_sleep;
	int				num_of_eat;
	long			start;
}				t_input;

typedef struct s_philo
{
	pthread_t			thread;
	int					isdead;
	t_all				*all;
	long				last_eat;
	int					count_eat;
	int					id;
	int					stop;
	t_input				params;
}				t_philo;

typedef struct s_all
{
	int		dead;
	int		isfull;
	pid_t	*pid;
	t_philo	*philosofers;
	sem_t	*forks;
	sem_t	*rights_to_write;
	sem_t	*eat_check;
	t_input	input;
}				t_all;

int		init_sem(t_all *all);
int		init_input(int argc, char **argv, t_all *all);
void	init_philosofers(int num_of_philos, t_all *all);
int		check_argv(int argc, char **argv);
int		ft_atoi(char *str);
long	gettime(long start);
void	ft_usleep(int in);
void	printstatus(long time, char *message, t_philo *philo, char *color);

void	take_fork(t_philo *philo);
void	eat(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);
void	kill_process(t_all *all);
int		check_death(t_philo	*philo);
void	ft_post_sem(t_all *all);

#endif