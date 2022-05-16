/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 19:27:50 by lxu-wu            #+#    #+#             */
/*   Updated: 2022/05/16 17:57:35 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdatomic.h>

typedef struct timeval	t_time;

typedef struct s_philo
{
	pthread_t		thread;
	int				name;
	pthread_mutex_t	lfork;
	pthread_mutex_t	*rfork;
	int				ate;
	int				die;
	size_t			last_meal;
	void			*data;
}	t_philo;

typedef struct s_input
{
	int	n_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eat_times;
}	t_input;

typedef struct s_data
{
	int				argc;
	char			**argv;
	t_input			input;
	size_t			start_time;
	t_philo			*philo;
	pthread_mutex_t	die;
	pthread_mutex_t	talk;
	pthread_mutex_t	meal;
	atomic_int		died;
	atomic_int		finish;
}	t_data;

int			ft_atoi_positive(const char *str);
void		ft_print_input(t_input input);
void		ft_wait_thread(t_data *data);
size_t		ft_current_time(void);
void		ft_usleep(size_t ms);

int			ft_destroy_fork(t_data *data, int n);
int			ft_free(void *var1, void *var2, void *var3, void *var4);
int			ft_destroy_all_mutex(t_data *data);

int			ft_take_info(t_data *data);
int			ft_init_mutex(t_data *data);
int			ft_init_thread(t_data *data);

int			ft_error(int e);

void		*ft_start_routine(void *param);

int			ft_init(t_data *data);

void		ft_check_dead(t_data *data);
int			ft_finish_to_eat(t_data *data);

#endif