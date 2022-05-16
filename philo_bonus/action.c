/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 19:27:55 by lxu-wu            #+#    #+#             */
/*   Updated: 2022/05/16 15:29:55 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_log(t_philo *philo, t_data *data, int e)
{
	sem_wait(data->talk);
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
	sem_post(data->talk);
}

void	ft_die_action(t_data *data, t_philo *philo)
{
	printf("%zu %d died\n", ft_current_time()
		- data->start_time, philo->name);
	while (data->input.n_philo > 1 && philo->taken-- > 0)
		sem_post(data->fork);
	exit(ft_free(data->philo, data->check_pros, data, 0));
}

void	*ft_check_died(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	int		i;

	philo = arg;
	data = philo->data;
	i = 0;
	while (philo->ate != data->input.eat_times)
	{
		sem_wait(data->talk);
		if (ft_current_time() - philo->last_meal > data->input.time_to_die)
		{
			if (ft_current_time() - philo->last_meal <= data->input.time_to_die)
			{
				sem_post(data->talk);
				continue ;
			}
			ft_die_action(data, philo);
		}
		sem_post(data->talk);
	}
	return (0);
}

void	ft_action(t_data *data, t_philo *philo)
{
	ft_take_fork(data, philo);
	philo->last_meal = ft_current_time();
	ft_log(philo, data, 2);
	ft_can_doing(data);
	ft_usleep(data->input.time_to_eat);
	sem_post(data->fork);
	philo->taken--;
	sem_post(data->fork);
	philo->taken--;
	sem_post(data->start);
	philo->ate++;
	ft_log(philo, data, 3);
	ft_can_doing(data);
	ft_usleep(data->input.time_to_sleep);
	ft_log(philo, data, 4);
}

void	ft_routine(t_data *data, t_philo *philo)
{
	philo->taken = 0;
	philo->last_meal = data->start_time;
	if (pthread_create(&philo->check_die, 0, ft_check_died, (void *)philo))
	{
		ft_free(data->philo, data->check_pros, data, 0);
		exit(1);
	}
	if (pthread_detach(philo->check_die))
	{
		ft_free(data->philo, data->check_pros, data, 0);
		exit(1);
	}
	if (data->input.n_philo > 1 && philo->name > (data->input.n_philo / 2))
		ft_usleep(data->input.time_to_eat / 10);
	while (1)
	{
		if (philo->ate == data->input.eat_times)
		{
			exit(0);
			ft_free(data->philo, data->check_pros, data, 0);
		}
		ft_action(data, philo);
	}
}
