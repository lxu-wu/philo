/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 19:27:45 by lxu-wu            #+#    #+#             */
/*   Updated: 2022/05/16 18:17:55 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init(t_data *data)
{
	if (ft_take_info(data))
		return (ft_error(1));
	if (ft_init_mutex(data) || ft_init_thread(data))
	{
		write(2, "Init error\n", 11);
		return (ft_free(data->philo, 0, 0, 0));
	}
	return (0);
}

int	ft_error(int e)
{
	if (e == 1)
		write(2, "At least one wrong input\n", 25);
	else if (e == 2)
		write(2, "\033[0;31mWARNING too much philo\033[0m\n", 34);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 5 && argc != 6)
	{
		write(2, "please use 5 or 6 arguments\n", 28);
		return (1);
	}
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	data->argc = argc;
	data->argv = argv;
	if (ft_init(data))
		return (1);
	ft_wait_thread(data);
	ft_destroy_all_mutex(data);
	return (0);
}
