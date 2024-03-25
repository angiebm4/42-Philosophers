/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:05:27 by abarrio-          #+#    #+#             */
/*   Updated: 2024/03/25 12:30:28 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	choose_fork(t_philo *philo)
{
	if(philo->who % 2 == 0)
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
	philo->last_time_eat = get_time();
	ft_usleep(philo->data->info.time_eat);
	philo->times_eat += 1;
	
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->rigth_fork);
	
	return (0);
}

int	end_pthread(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_manage);
	if (philo->data->end_program == 1)
	{
		pthread_mutex_unlock(&philo->data->mutex_manage);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex_manage);
	
    if (philo->times_eat== philo->data->info.times_must_eat)
    {
		pthread_mutex_lock(&philo->philo_manage);
        philo->satisfied = 1;
		pthread_mutex_unlock(&philo->philo_manage);
        return (1);
    }
	
    if ((get_time() - philo->last_time_eat) > philo->data->info.time_die)
	{
		print_state(philo, DEATH);
        pthread_mutex_lock(&philo->philo_manage);
		philo->die = 1;
        pthread_mutex_unlock(&philo->philo_manage);
		return (1);
	}

	return (0);
}
int	rutine_manage(t_philo *philo)
{
	while(1)
	{
		if (end_pthread(philo) == 0)
            ft_eat(philo);
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

void	*rutine(void *src)
{
    t_philo	*philo;

	philo = (t_philo*)src;
    
    while (1)
    {
        pthread_mutex_lock(&philo->data->start_mutex);
        if (philo->data->init_program == 0)
        {
            pthread_mutex_unlock(&philo->data->start_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->data->start_mutex);
    }
	
    if (rutine_manage(philo) == 0)
        return (NULL);
    return (NULL);
}