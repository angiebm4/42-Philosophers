/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutine_habits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:36:25 by abarrio-          #+#    #+#             */
/*   Updated: 2024/04/25 14:29:07 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	take_fork(t_fork *fork)
{
	int ret;

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

void	ft_thinking(t_philo *philo)
{
	print_state(philo, THINKING);
	if (philo->data->info.nb_philo % 2 != 0)
		ft_usleep(philo->data->info.time_eat * 2 - philo->data->info.time_sleep);
		
}

void	ft_sleep(t_philo *philo)
{
	print_state(philo, SLEEPING);
	ft_usleep(philo->data->info.time_sleep);
}

int	take_rigth_fork(t_data *data, int nb, int rigth)
{
	(void)rigth;
	while (1)
	{
		if (take_fork(data->philo[nb - 1].rigth_fork) == 1)
		{
			break;
			/*pthread_mutex_lock(&data->philo[rigth].philo_manage);
			if (data->philo[rigth].last_time_eat >= data->philo[nb - 1].last_time_eat)
			{
				pthread_mutex_unlock(&data->philo[rigth].philo_manage);
				print_state(&data->philo[nb - 1], TAKING_A_FORK_R);
				break ;
			}
			pthread_mutex_unlock(&data->philo[rigth].philo_manage);
			pthread_mutex_lock(&data->philo[nb - 1].rigth_fork->mutex_fork);
			data->philo[nb - 1].rigth_fork->fork = 0;
			pthread_mutex_unlock(&data->philo[nb - 1].rigth_fork->mutex_fork);*/
		}
		if (end_pthread(&data->philo[nb - 1]) == 1)
		{
			pthread_mutex_unlock(&data->philo[nb - 1].rigth_fork->mutex_fork);
			return (1);
		}	
	}
	return (0);
}

int	take_left_fork(t_data *data, int nb, int left)
{
	(void)left;
	while (1)
	{
		if (take_fork(data->philo[nb - 1].left_fork) == 1)
		{
			break;
			/*pthread_mutex_lock(&data->philo[left].philo_manage);
			if (data->philo[left].last_time_eat >= data->philo[nb - 1].last_time_eat)
			{
				pthread_mutex_unlock(&data->philo[left].philo_manage);
				print_state(&data->philo[nb - 1], TAKING_A_FORK_L);
				break ;
			}
			pthread_mutex_unlock(&data->philo[left].philo_manage);
			pthread_mutex_lock(&data->philo[nb - 1].rigth_fork->mutex_fork);
			data->philo[nb - 1].rigth_fork->fork = 0;
			pthread_mutex_unlock(&data->philo[nb - 1].rigth_fork->mutex_fork);*/
		}
		if (end_pthread(&data->philo[nb - 1]) == 1)
		{
			return (1);
		}	
	}
	return (0);
}


static int choose_fork(t_philo *philo)
{
	int	left;
	int rigth;

	left = 0;
	rigth = philo->who;
	if (philo->who == 1)
		left = philo->data->info.nb_philo - 1;
	else if (philo->who == philo->data->info.nb_philo)
		rigth = philo->who - 1;
	else
		left = philo->who - 2;
	if (philo->who % 2 == 0)
	{
		if (take_rigth_fork(philo->data, philo->who, rigth) == 1)
			return (1);
		if (take_left_fork(philo->data, philo->who, left) == 1)
		{
			return (1);
		}
	}
	else
	{
		if (take_left_fork(philo->data, philo->who, left) == 1)
			return (1);
		if (take_rigth_fork(philo->data, philo->who, rigth) == 1)
		{
			return (1);
		}
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
	pthread_mutex_lock(&philo->left_fork->mutex_fork);
	pthread_mutex_lock(&philo->rigth_fork->mutex_fork);
	philo->left_fork->fork = 0;
	philo->rigth_fork->fork = 0;
	print_state(philo, LET_FORKS);
	print_state(philo, LET_FORKS);
	pthread_mutex_unlock(&philo->left_fork->mutex_fork);
	pthread_mutex_unlock(&philo->rigth_fork->mutex_fork);
	return (0);
}
