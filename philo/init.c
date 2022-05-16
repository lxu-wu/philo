/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 20:37:52 by lxu-wu            #+#    #+#             */
/*   Updated: 2022/05/16 18:12:31 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_take_info(t_data *data)
{
	data->input.n_philo = ft_atoi_positive(data->argv[1]);
	if (data->input.n_philo < 1 || data->input.n_philo > 200)
		return (1);
	data->input.time_to_die = ft_atoi_positive(data->argv[2]);
	if (data->input.time_to_die < 60)
		return (1);
	data->input.time_to_eat = ft_atoi_positive(data->argv[3]);
	if (data->input.time_to_eat < 60)
		return (1);
	data->input.time_to_sleep = ft_atoi_positive(data->argv[4]);
	if (data->input.time_to_sleep < 60)
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

int	ft_init_mutex(t_data *data)
{
	size_t	i;

	i = -1;
	data->philo = malloc(sizeof(t_philo) * (data->input.n_philo));
	if (!data->philo)
		return (1);
	data->philo = memset(data->philo, 0, (data->input.n_philo));
	while (++i < (size_t)data->input.n_philo)
		if (pthread_mutex_init(&data->philo[i].lfork, 0))
			return (ft_destroy_fork(data, i));
	if (pthread_mutex_init(&data->talk, 0))
		return (ft_destroy_fork(data, data->input.n_philo));
	if (pthread_mutex_init(&data->meal, 0))
	{
		pthread_mutex_destroy(&data->talk);
		return (ft_destroy_fork(data, data->input.n_philo));
	}
	if (pthread_mutex_init(&data->die, 0))
	{
		pthread_mutex_destroy(&data->meal);
		pthread_mutex_destroy(&data->talk);
		return (ft_destroy_fork(data, data->input.n_philo));
	}
	return (0);
}

int	ft_init_thread(t_data *data)
{
	size_t	i;

	i = 0;
	data->died = 0;
	data->start_time = ft_current_time();
	data->finish = 0;
	while (i < (size_t)data->input.n_philo)
	{
		data->philo[i].die = 0;
		data->philo[i].name = i + 1;
		data->philo[i].rfork = &data->philo[(i + 1)
			% data->input.n_philo].lfork;
		data->philo[i].ate = 0;
		data->philo[i].die = 0;
		data->philo[i].data = data;
		data->philo[i].last_meal = data->start_time;
		if (pthread_create(&data->philo[i].thread,
				0, &ft_start_routine, &data->philo[i]))
			return (ft_destroy_all_mutex(data));
		i++;
	}
	ft_check_dead(data);
	return (0);
}
