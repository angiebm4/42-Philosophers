/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:21:06 by abarrio-          #+#    #+#             */
/*   Updated: 2024/04/26 10:55:20 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	take_fork(t_fork *fork)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&fork->mutex_fork);
	if (fork->fork == 0)
	{
		fork->fork = 1;
		ret = 1;
	}
	pthread_mutex_unlock(&fork->mutex_fork);
	return (ret);
}

static int	take_rigth_fork(t_data *data, int nb)
{
	while (1)
	{
		if (take_fork(data->philo[nb - 1].rigth_fork) == 1)
		{
			print_state(&data->philo[nb - 1], TAKING_A_FORK_R);
			break ;
		}
		if (end_pthread(&data->philo[nb - 1]) == 1)
			return (1);
	}
	return (0);
}

static int	take_left_fork(t_data *data, int nb)
{
	while (1)
	{
		if (take_fork(data->philo[nb - 1].left_fork) == 1)
		{
			print_state(&data->philo[nb - 1], TAKING_A_FORK_L);
			break ;
		}
		if (end_pthread(&data->philo[nb - 1]) == 1)
			return (1);
	}
	return (0);
}

int	choose_fork(t_philo *philo)
{
	if (philo->who % 2 == 0)
	{
		if (take_rigth_fork(philo->data, philo->who) == 1)
			return (1);
		if (take_left_fork(philo->data, philo->who) == 1)
			return (1);
	}
	else
	{
		if (take_left_fork(philo->data, philo->who) == 1)
			return (1);
		if (take_rigth_fork(philo->data, philo->who) == 1)
			return (1);
	}
	return (0);
}
