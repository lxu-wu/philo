/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 20:37:18 by lxu-wu            #+#    #+#             */
/*   Updated: 2022/05/13 12:43:41 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_free(void *a, void *b, void *c, void *d)
{
	free(a);
	free(b);
	free(c);
	free(d);
	return (1);
}

void	ft_unlink(void)
{
	sem_unlink("sem_fork");
	sem_unlink("sem_talk");
	sem_unlink("sem_start");
}

int	ft_close(sem_t *a, sem_t *b, sem_t *c)
{
	if (a)
		sem_close(a);
	if (b)
		sem_close(b);
	if (c)
		sem_close(c);
	return (1);
}

int	ft_close_exit(sem_t *a, sem_t *b, sem_t *c, t_data *data)
{
	if (a)
		sem_close(a);
	if (b)
		sem_close(b);
	if (c)
		sem_close(c);
	if (data)
		free(data);
	exit(1);
}

int	ft_kill(t_data *data, size_t limit)
{
	size_t	i;

	i = 0;
	ft_close(data->start, data->fork, data->talk);
	while (i <= limit)
	{
		kill(data->philo[i].pid, SIGKILL);
		i++;
	}
	ft_unlink();
	return (1);
}
