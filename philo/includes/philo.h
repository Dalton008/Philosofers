/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 13:36:46 by mjammie           #+#    #+#             */
/*   Updated: 2021/06/20 16:18:32 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <sys/time.h>

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
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
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
	t_philo				*philosofers;
	pthread_mutex_t		*forks;
	t_input				input;
	pthread_mutex_t		rights_to_write;
}				t_all;

int			init_input(int argc, char **argv, t_all *all);
void		init_philosofers(int num_of_philos, t_all *all);
void		init_forks(t_all *all);
void		give_forks(t_all *all);
int			ft_atoi(char *str);
int			check_argv(int argc, char **argv);

long		gettime(long start);
void		take_fork(t_philo *philo);
void		eat(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);
void		ft_usleep(int in);

void		printstatus(long time, char *message, t_philo *philo, char *color);
void		free_all(t_all *all);

#endif