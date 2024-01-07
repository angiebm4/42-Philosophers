/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:15:59 by abarrio-          #+#    #+#             */
/*   Updated: 2024/01/07 15:23:03 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_eat(t_philo *philo)
{
	if (doctor(philo) == 1)
		return (1);
	// print_state(philo, THINKING); como esperar a que se desbloqueen los mutex
	if (doctor(philo) == 1)
		return (1);
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, TAKING_A_FORK_L);
	if (doctor(philo) == 1)
		return (1);
	pthread_mutex_lock(philo->rigth_fork);
	print_state(philo, TAKING_A_FORK_R);
	if (doctor(philo) == 1)
		return (1);
	if ((get_time() - philo->last_time_eat) < philo->data->time_die)
		philo->data->philo_death = 1;
	print_state(philo, EATING);
	usleep(philo->data->time_eat * 1000);
	philo->last_time_eat = philo->data->start_time - get_time();
	philo->times_eat += 1;
	if (doctor(philo) == 1)
		return (1);
	// if ((philo->data->times_must_eat > 0) && philo->times_eat == (size_t)philo->data->times_must_eat)
	// 	philo->data->all_satisfied += 1;
	// if (philo->data->time_die < philo->last_time_eat)
	// 	philo->data->philo_death = 1;
	printf("filo %zu --- dejo de usar el tenedor left\n", philo->who);
	pthread_mutex_unlock(philo->left_fork);
	printf("filo %zu --- dejo de usar el tenedor rigth\n", philo->who);
	pthread_mutex_unlock(philo->rigth_fork);
	if (doctor(philo) == 1)
		return (1);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	if (doctor(philo) == 1)
		return (1);
	print_state(philo, SLEEPING);
	usleep(philo->data->time_sleep * 1000);
	return (0);
}


void	*rutine(void *src)
{
	t_philo	*philo;

	philo = src;
	while (philo->data->init_program == 1)
		usleep(1000);
	while(1)
	{
		if (ft_eat(philo) == 1)
			return (NULL);
		if (ft_sleep(philo) == 1)
			return (NULL);
	}
	return (NULL);
}
