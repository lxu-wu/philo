/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 19:28:12 by lxu-wu            #+#    #+#             */
/*   Updated: 2022/05/13 12:34:46 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_usleep(size_t ms)
{
	size_t	t1;

	t1 = ft_current_time();
	while (ft_current_time() - t1 < ms)
	{
		usleep(50);
	}
}

void	ft_can_doing(t_data *data)
{
	sem_wait(data->talk);
	sem_post(data->talk);
}

void	ft_take_fork(t_data *data, t_philo *philo)
{
	sem_wait(data->start);
	sem_wait(data->fork);
	philo->taken++;
	ft_log(philo, data, 1);
	sem_wait(data->fork);
	philo->taken++;
	ft_log(philo, data, 1);
}
