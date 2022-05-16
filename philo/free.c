/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 19:27:41 by lxu-wu            #+#    #+#             */
/*   Updated: 2022/05/12 20:37:10 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_destroy_fork(t_data *data, int n)
{
	size_t	i;

	i = 0;
	while ((int)i < n)
		pthread_mutex_destroy(&data->philo[i++].lfork);
	free(data->philo);
	data->philo = 0;
	free(data);
	data = 0;
	return (1);
}

int	ft_free(void *var1, void *var2, void *var3, void *var4)
{
	free(var1);
	free(var2);
	free(var3);
	free(var4);
	var1 = 0;
	var2 = 0;
	var3 = 0;
	var4 = 0;
	return (1);
}

int	ft_destroy_all_mutex(t_data *data)
{
	pthread_mutex_destroy(&data->die);
	pthread_mutex_destroy(&data->meal);
	pthread_mutex_destroy(&data->talk);
	return (ft_destroy_fork(data, data->input.n_philo));
}
