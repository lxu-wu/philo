/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 20:37:47 by lxu-wu            #+#    #+#             */
/*   Updated: 2022/05/16 15:27:45 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_log(t_philo *philo, t_data *data, int e)
{
	pthread_mutex_lock(&data->talk);
	if (data->died)
	{
		pthread_mutex_unlock(&data->talk);
		return ;
	}
	if (e == 1)
		printf("%zu %d has taken a fork\n", ft_current_time()
			- data->start_time, philo->name);
	else if (e == 2)
		printf("%zu %d is eating\n", ft_current_time()
			- data->start_time, philo->name);
	else if (e == 3)
		printf("%zu %d is sleeping\n", ft_current_time()
			- data->start_time, philo->name);
	else if (e == 4)
		printf("%zu %d is thinking\n", ft_current_time()
			- data->start_time, philo->name);
	pthread_mutex_unlock(&data->talk);
}

void	ft_check_dead(t_data *data)
{
	int		i;
	size_t	die;

	i = 0;
	while (!data->died)
	{	
		if (i == data->input.n_philo)
			i = 0;
		pthread_mutex_lock(&data->meal);
		die = ft_current_time() - data->philo[i].last_meal
			> (size_t)data->input.time_to_die;
		if (die)
		{
			pthread_mutex_lock(&data->talk);
			data->died = 1;
			printf("%zu %d died\n", ft_current_time()
				- data->start_time, data->philo[i].name);
			pthread_mutex_unlock(&data->talk);
		}
		i++;
		pthread_mutex_unlock(&data->meal);
	}
}

void	ft_action(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(philo->rfork);
	ft_log(philo, data, 1);
	pthread_mutex_lock(&philo->lfork);
	ft_log(philo, data, 1);
	pthread_mutex_lock(&data->meal);
	philo->last_meal = ft_current_time();
	pthread_mutex_unlock(&data->meal);
	ft_log(philo, data, 2);
	if (!data->died)
		ft_usleep(data->input.time_to_eat);
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(&philo->lfork);
	philo->ate++;
	ft_log(philo, data, 3);
	if (!data->died)
		ft_usleep(data->input.time_to_sleep);
	ft_log(philo, data, 4);
}

void	*ft_start_routine(void *param)
{
	t_data	*data;
	t_philo	*philo;

	philo = (t_philo *)param;
	data = (t_data *)philo->data;
	if (philo->name % 2 == 0)
		ft_usleep(data->input.time_to_eat / 10);
	while (!data->died)
	{
		if (philo->ate == data->input.eat_times)
			break ;
		if (!data->died && &philo->lfork != philo->rfork)
			ft_action(philo, data);
		else
		{
			ft_log(philo, data, 1);
			return (0);
		}
	}
	return (0);
}
