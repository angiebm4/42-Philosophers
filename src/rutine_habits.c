/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutine_habits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:36:25 by abarrio-          #+#    #+#             */
/*   Updated: 2024/04/21 15:18:47 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_thinking(t_philo *philo)
{
	print_state(philo, THINKING);
}

void	ft_sleep(t_philo *philo)
{
	print_state(philo, SLEEPING);
	ft_usleep(philo->data->info.time_sleep);
}

static void	choose_fork(t_philo *philo)
{
	if (philo->who % 2 == 0)
	{
		pthread_mutex_lock(&philo->rigth_fork->mutex_fork);
		philo->rigth_fork->fork = 1;
		print_state(philo, TAKING_A_FORK_R);
		pthread_mutex_lock(&philo->left_fork->mutex_fork);
		philo->left_fork->fork = 1;
		print_state(philo, TAKING_A_FORK_L);
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->mutex_fork);
		philo->left_fork->fork = 1;
		print_state(philo, TAKING_A_FORK_L);
		pthread_mutex_lock(&philo->rigth_fork->mutex_fork);
		philo->rigth_fork->fork = 1;
		print_state(philo, TAKING_A_FORK_R);
	}
}

int	ft_eat(t_philo *philo)
{
	choose_fork(philo);
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
