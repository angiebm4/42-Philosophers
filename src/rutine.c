/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:05:27 by abarrio-          #+#    #+#             */
/*   Updated: 2024/04/26 11:06:35 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	end_pthread(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_manage);
	if (philo->data->end_program == 1)
	{
		pthread_mutex_unlock(&philo->data->mutex_manage);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex_manage);
	if (philo->times_eat == philo->data->info.times_must_eat)
	{
		pthread_mutex_lock(&philo->philo_manage);
		philo->satisfied = 1;
		pthread_mutex_unlock(&philo->philo_manage);
		return (1);
	}
	return (0);
}

int	rutine_manage(t_philo *philo)
{
	if (philo->who % 2 == 0)
		ft_usleep(philo->data->info.time_eat);
	while (1)
	{
		if (end_pthread(philo) == 0)
		{
			if (ft_eat(philo) == 1)
				return (1);
		}
		else
			return (1);
		if (end_pthread(philo) == 0)
			ft_sleep(philo);
		else
			return (1);
		if (end_pthread(philo) == 0)
			ft_thinking(philo);
		else
			return (1);
	}
	return (0);
}

void	*one_philo(t_philo *philo)
{
	print_state(philo, TAKING_A_FORK_R);
	ft_usleep(philo->data->info.time_die);
	return (NULL);
}

void	*no_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_manage);
	philo->satisfied = 1;
	pthread_mutex_unlock(&philo->philo_manage);
	return (NULL);
}

void	*rutine(void *src)
{
	t_philo	*philo;

	philo = (t_philo *)src;
	while (1)
	{
		pthread_mutex_lock(&philo->data->start_mutex);
		if (philo->data->init_program == 0)
		{
			pthread_mutex_unlock(&philo->data->start_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->start_mutex);
	}
	if (philo->data->info.nb_philo == 1)
		return (one_philo(philo));
	if (philo->data->info.times_must_eat == 0)
		return (no_meals(philo));
	if (rutine_manage(philo) == 0)
		return (NULL);
	return (NULL);
}
