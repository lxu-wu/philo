/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 19:28:09 by lxu-wu            #+#    #+#             */
/*   Updated: 2022/05/16 18:15:26 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	*ft_check_stop_pros(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	int		ret;

	philo = arg;
	data = philo->data;
	waitpid(philo->pid, &ret, 0);
	if (ret == 256)
	{
		ft_kill(data, data->input.n_philo - 1);
	}
	return (0);
}

void	ft_wait_thread(t_data *data)
{
	size_t	i;

	i = 0;
	while ((int)i < data->input.n_philo)
		pthread_join(data->check_pros[i++], 0);
}

void	ft_wait(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->input.n_philo)
		pthread_create(&data->check_pros[i], 0,
			ft_check_stop_pros, &data->philo[i]);
	ft_wait_thread(data);
}

size_t	ft_current_time(void)
{
	t_time	time;

	gettimeofday(&time, 0);
	return (1000 * time.tv_sec + time.tv_usec / 1000);
}
