/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutine_habits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:36:25 by abarrio-          #+#    #+#             */
/*   Updated: 2024/04/19 14:07:48 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_death(t_philo *philo, int flag)
{
	pthread_mutex_lock(&philo->philo_manage);
	if ((get_time() - philo->last_time_eat) > philo->data->info.time_die)
	{
		if (flag == 1)
		{
			philo->left_fork->fork = 0;
			philo->rigth_fork->fork = 0;
			pthread_mutex_unlock(&philo->left_fork->mutex_fork);
			pthread_mutex_unlock(&philo->rigth_fork->mutex_fork);
		}
		else if (flag == 2)
		{
			philo->rigth_fork->fork = 0;
			pthread_mutex_unlock(&philo->rigth_fork->mutex_fork);
		}
		else if (flag == 3)
		{
			philo->left_fork->fork = 0;
			pthread_mutex_unlock(&philo->left_fork->mutex_fork);
		}
		pthread_mutex_unlock(&philo->philo_manage);
		return (1);
	}
	pthread_mutex_unlock(&philo->philo_manage);
	return (0);
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
