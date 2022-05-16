/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 20:37:24 by lxu-wu            #+#    #+#             */
/*   Updated: 2022/05/16 15:27:35 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_take_info(t_data *data)
{
	data->input.n_philo = ft_atoi_positive(data->argv[1]);
	if (data->input.n_philo < 1 || data->input.n_philo > 200)
		return (1);
	data->input.time_to_die = ft_atoi_positive(data->argv[2]);
	if (data->input.time_to_die < 0 || data->input.time_to_die < 60)
		return (1);
	data->input.time_to_eat = ft_atoi_positive(data->argv[3]);
	if (data->input.time_to_eat < 0 || data->input.time_to_eat < 60)
		return (1);
	data->input.time_to_sleep = ft_atoi_positive(data->argv[4]);
	if (data->input.time_to_sleep < 0 || data->input.time_to_sleep < 60)
		return (1);
	data->input.eat_times = -1;
	if (data->argc == 6)
	{
		data->input.eat_times = ft_atoi_positive(data->argv[5]);
		if (data->input.eat_times < 0)
			return (1);
	}
	if (data->input.n_philo >= 50)
		ft_error(2);
	return (0);
}

int	ft_init_sem(t_data *data)
{
	ft_unlink();
	data->fork = sem_open("sem_fork", O_CREAT, 0644, data->input.n_philo);
	if (data->fork == SEM_FAILED)
		return (1);
	data->start = sem_open("sem_start", O_CREAT, 0644,
			(int)(data->input.n_philo / 2));
	if (data->start == SEM_FAILED)
		return (ft_close(data->fork, 0, 0));
	data->talk = sem_open("sem_talk", O_CREAT, 0644, 1);
	if (data->talk == SEM_FAILED)
		return (ft_close(data->start, data->fork, 0));
	if (data->input.n_philo == 1)
	{
		sem_post(data->start);
		sem_post(data->talk);
	}
	return (0);
}

int	ft_init_pros(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->input.n_philo);
	data->check_pros = malloc(sizeof(t_philo) * data->input.n_philo);
	if (!data->philo || (!data->check_pros && ft_free(data->philo, 0, 0, 0)))
		ft_close_exit(data->start, data->fork, data->talk, data);
	data->start_time = ft_current_time();
	while (i < data->input.n_philo)
	{
		data->philo[i].ate = 0;
		data->philo[i].name = i + 1;
		data->philo[i].data = data;
		data->philo[i].pid = fork();
		if (data->philo[i].pid == -1)
			return (ft_close(data->start, data->fork, data->talk)
				&& ft_kill(data, i));
		if (!data->philo[i].pid)
			ft_routine(data, &data->philo[i]);
		i++;
	}
	return (0);
}
