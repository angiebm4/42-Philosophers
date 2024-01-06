/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:15:59 by abarrio-          #+#    #+#             */
/*   Updated: 2024/01/06 20:25:12 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->rigth_fork);
	print_state(philo, EATING);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->rigth_fork);
}


void	*rutine(void *src)
{
	t_philo	*philo;

	philo = src;
	while (philo->data->init_program == 1)
		usleep(1);
	eat(philo);
	
	return (NULL);
}
