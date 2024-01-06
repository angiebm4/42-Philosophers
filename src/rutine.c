/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:15:59 by abarrio-          #+#    #+#             */
/*   Updated: 2024/01/06 21:52:43 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->rigth_fork);
	print_state(philo, EATING);
	philo->last_time_eat = philo->data->start_time - get_time();
	if (philo->data->time_die < philo->last_time_eat)
		philo->data->philo_death = 1;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->rigth_fork);
}

void	ft_sleep(t_philo *philo)
{
	print_state(philo, SLEEPING);
	usleep(philo->data->time_sleep * 1000);
}

void	*rutine(void *src)
{
	t_philo	*philo;

	philo = src;
	while (philo->data->init_program == 1)
		usleep(1);
	while(philo->data->philo_death == 0)
	{
		if (philo->data->time_die < philo->last_time_eat || philo->data->time_die < (get_time() - philo->data->start_time))
			print_state(philo, DEATH);
		ft_eat(philo);
		ft_sleep(philo);
	}
	return (NULL);
}
