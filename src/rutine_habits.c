/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutine_habits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:36:25 by abarrio-          #+#    #+#             */
/*   Updated: 2024/04/26 11:14:53 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_thinking(t_philo *philo)
{
	print_state(philo, THINKING);
	if (philo->data->info.nb_philo % 2 != 0)
		ft_usleep(philo->data->info.time_eat * 2
			- philo->data->info.time_sleep);
}

void	ft_sleep(t_philo *philo)
{
	print_state(philo, SLEEPING);
	ft_usleep(philo->data->info.time_sleep);
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
	pthread_mutex_lock(&philo->left_fork->mutex_fork);
	pthread_mutex_lock(&philo->rigth_fork->mutex_fork);
	philo->left_fork->fork = 0;
	philo->rigth_fork->fork = 0;
	pthread_mutex_unlock(&philo->left_fork->mutex_fork);
	pthread_mutex_unlock(&philo->rigth_fork->mutex_fork);
	return (0);
}
