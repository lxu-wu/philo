/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 19:27:34 by lxu-wu            #+#    #+#             */
/*   Updated: 2022/05/16 18:15:37 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi_positive(const char *str)
{
	size_t	i;
	size_t	nb;

	i = 0;
	nb = 0;
	if (!str || !str[i])
		return (-1);
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		nb = nb * 10 + (str[i++] - 48);
		if (nb > 2147483647)
			return (-1);
	}
	if (str[i])
		return (-1);
	return (nb);
}

void	ft_wait_thread(t_data *data)
{
	size_t	i;

	i = 0;
	while ((int)i < data->input.n_philo)
		pthread_join(data->philo[i++].thread, 0);
}

size_t	ft_current_time(void)
{
	t_time	time;

	gettimeofday(&time, 0);
	return (1000 * time.tv_sec + time.tv_usec / 1000);
}

void	ft_usleep(size_t ms)
{
	size_t	t1;

	t1 = ft_current_time();
	while (ft_current_time() - t1 < ms)
	{
		usleep(50);
	}
}
