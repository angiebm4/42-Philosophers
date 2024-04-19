/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:07:06 by abarrio-          #+#    #+#             */
/*   Updated: 2024/04/19 14:07:36 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	choose_even(t_philo *philo)
{
	pthread_mutex_lock(&philo->rigth_fork->mutex_fork);
	philo->rigth_fork->fork = 1;
	if (is_death(philo, 2))
		return (1);
	print_state(philo, TAKING_A_FORK_R);
	pthread_mutex_lock(&philo->left_fork->mutex_fork);
	philo->left_fork->fork = 1;
	if (is_death(philo, 1))
		return (1);
	print_state(philo, TAKING_A_FORK_L);
	return (0);
}

static int	choose_odd(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex_fork);
	philo->left_fork->fork = 1;
	if (is_death(philo, 3))
		return (1);
	print_state(philo, TAKING_A_FORK_L);
	pthread_mutex_lock(&philo->rigth_fork->mutex_fork);
	philo->rigth_fork->fork = 1;
	if (is_death(philo, 1))
		return (1);
	print_state(philo, TAKING_A_FORK_R);
	return (0);
}

static int	choose_fork(t_philo *philo)
{
	if (philo->who % 2 == 0)
	{
		if (choose_even(philo) == 1)
			return (1);
	}
	else
	{
		if (choose_odd(philo) == 1)
			return (1);
	}
	return (0);
}

int	ft_eat(t_philo *philo)
{
	if (choose_fork(philo) == 1)
		return (1);
	pthread_mutex_lock(&philo->philo_manage);
	philo->last_time_eat = get_time();
	pthread_mutex_unlock(&philo->philo_manage);
	print_state(philo, EATING);
	ft_usleep(philo->data->info.time_eat);
	philo->times_eat += 1;
	philo->left_fork->fork = 0;
	philo->rigth_fork->fork = 0;
	pthread_mutex_unlock(&philo->left_fork->mutex_fork);
	pthread_mutex_unlock(&philo->rigth_fork->mutex_fork);
	return (0);
}
