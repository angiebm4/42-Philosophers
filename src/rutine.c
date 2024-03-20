/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:05:27 by abarrio-          #+#    #+#             */
/*   Updated: 2024/03/20 19:21:38 by angela           ###   ########.fr       */
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
	usleep(philo->data->info.time_sleep * 1000);
}

int	ft_eat(t_philo *philo)
{
	choose_fork(philo);
	if ((get_time() - philo->last_time_eat) > philo->data->info.time_die)
	{
		pthread_mutex_lock(&philo->mutex_philo);
		print_state(philo, DEATH);
		philo->die = 1;
		pthread_mutex_unlock(&philo->mutex_philo);
		return (1);
	}
	print_state(philo, EATING);
	usleep(philo->data->info.time_eat * 1000);
	philo->last_time_eat = get_time();
	philo->times_eat += 1;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->rigth_fork);
	if (philo->times_eat == philo->data->info.times_must_eat)
	{
		pthread_mutex_lock(&philo->data->mutex_manage);
		philo->data->all_satisfied += 1;
		pthread_mutex_unlock(&philo->data->mutex_manage);
		return (1);
	}
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
	return (0);
}
int	rutine_manage(t_philo *philo)
{
	while(1)
	{
		if (end_pthread(philo) == 0)
		{
			if (ft_eat(philo) == 1)
				return (1);
		}
		if (end_pthread(philo) == 0)
			ft_sleep(philo);
		if (end_pthread(philo) == 0)
			ft_thinking(philo);
		if (end_pthread(philo) == 1)
			return (1);
	}
	return (0);
}

void	*rutine(void *src)
{
	t_philo	*philo;

	// return (NULL);
	philo = (t_philo*)src;
	while (philo->data->init_program == 1)
		usleep(10);
	if (philo->data->info.nb_philo == 1)
	{
		usleep(philo->data->info.time_die);
		print_state(philo, DEATH);
		printf(CYAN"loneliness is not the best buddy for philosophers\n"CLEAR);
		return (NULL); // se tiene que morir??
	}
	if (philo->data->info.times_must_eat == 0)
	{
		printf(GREENFOSFI"bro bro let us eattt fuuckkk!!?¿¿¿¡¡¡!\n"CLEAR);
		return (NULL);
	}
	if (rutine_manage(philo) == 1)
		return (NULL);
	// ft_eat(philo);
	printf("2 --- paso por aqui %zu\n", philo->who);
	// hasta aqui esta bien tengo que gestionar el doctor y demas algo no va bien
	return (NULL);
}
