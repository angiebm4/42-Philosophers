/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutine_habits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:36:25 by abarrio-          #+#    #+#             */
/*   Updated: 2024/04/03 22:38:25 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	choose_fork(t_philo *philo)
{
	if (philo->who % 2 == 0)
	{
		pthread_mutex_lock(philo->rigth_fork);
		print_state(philo, TAKING_A_FORK_R);
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, TAKING_A_FORK_L);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, TAKING_A_FORK_L);
		pthread_mutex_lock(philo->rigth_fork);
		print_state(philo, TAKING_A_FORK_R);
	}
}

void	ft_thinking(t_philo *philo)
{
	print_state(philo, THINKING);
}

void	ft_sleep(t_philo *philo)
{
	print_state(philo, SLEEPING);
	ft_usleep(philo->data->info.time_sleep);
}

int	ft_eat(t_philo *philo)
{
	choose_fork(philo);
	print_state(philo, EATING);
	if ((get_time() - philo->last_time_eat) > philo->data->info.time_die)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->rigth_fork);
		return (1);
	}
	philo->last_time_eat = get_time();
	ft_usleep(philo->data->info.time_eat);
	philo->times_eat += 1;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->rigth_fork);
	return (0);
}
