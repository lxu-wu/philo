/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 19:28:07 by lxu-wu            #+#    #+#             */
/*   Updated: 2022/05/16 18:16:37 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdatomic.h>
# include <semaphore.h>
# include <signal.h>

typedef struct timeval	t_time;

typedef struct s_philo
{
	pid_t			pid;
	int				name;
	atomic_int		ate;
	atomic_int		taken;
	atomic_ulong	last_meal;
	pthread_t		check_die;
	void			*data;
}	t_philo;

typedef struct s_input
{
	int		n_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		eat_times;
}	t_input;

typedef struct s_data
{
	int				argc;
	char			**argv;
	t_input			input;
	atomic_ulong	start_time;
	t_philo			*philo;
	sem_t			*fork;
	sem_t			*talk;
	sem_t			*start;
	pthread_t		*check_pros;
}	t_data;

int			ft_atoi_positive(const char *str);
void		ft_print_input(t_input input);
void		ft_wait(t_data *data);
size_t		ft_current_time(void);
void		ft_usleep(size_t ms);

int			ft_destroy_fork(t_data *data, int n);
int			ft_free(void *var1, void *var2, void *var3, void *var4);
int			ft_destroy_all_mutex(t_data *data);
int			ft_close(sem_t *a, sem_t *b, sem_t *c);
void		ft_unlink(void);
int			ft_close_exit(sem_t *a, sem_t *b, sem_t *c, t_data *data);
void		ft_can_doing(t_data *data);

int			ft_take_info(t_data *data);
int			ft_init_mutex(t_data *data);
int			ft_init_pros(t_data *data);
void		ft_take_fork(t_data *data, t_philo *philo);
void		ft_log(t_philo *philo, t_data *data, int e);
int			ft_init_sem(t_data *data);

int			ft_error(int e);

void		*ft_start_routine(void *param);

int			ft_init(t_data *data);

void		ft_check_dead(t_data *data);

void		ft_routine(t_data *data, t_philo *philo);

int			ft_kill(t_data *data, size_t limit);

#endif