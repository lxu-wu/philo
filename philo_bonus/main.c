/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 19:28:02 by lxu-wu            #+#    #+#             */
/*   Updated: 2022/05/12 20:45:20 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_init(t_data *data)
{
	if (ft_take_info(data))
		return (ft_error(1));
	if (ft_init_sem(data) || ft_init_pros(data))
	{
		write(2, "Init error\n", 11);
		ft_unlink();
		return (1);
	}
	return (0);
}

void	ft_print_input(t_input input)
{
	printf("n_philo = %d\n", input.n_philo);
	printf("time_to_die = %zu\n", input.time_to_die);
	printf("time_to_eat = %zu\n", input.time_to_eat);
	printf("time_to_sleep = %zu\n", input.time_to_sleep);
	printf("eat_times = %zu\n", input.eat_times);
}

int	ft_error(int e)
{
	if (e == 1)
		write(2, "At least a wrong input\n", 23);
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
	data->argc = argc;
	data->argv = argv;
	if (ft_init(data))
		return (1);
	ft_wait(data);
	ft_free(data->philo, data->check_pros, data, 0);
	return (0);
}
