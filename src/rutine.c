/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:05:27 by abarrio-          #+#    #+#             */
/*   Updated: 2024/03/09 12:33:42 by angela           ###   ########.fr       */
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

void	ft_thinking()
{
	
}

void	ft_sleep(t_philo *philo)
{
	
}

void	ft_eat(t_philo *philo)
{
	choose_fork(philo);
}

void	ft_eat(t_philo *philo)
{
	while (philo->data->end_program == 0)
	{
		printf("paso por aqui %zu\n", philo->who);
		choose_fork(philo);
		if ((get_time() - philo->last_time_eat) > philo->data->info.time_die)
		{
			print_state(philo, DEATH);
			//pthread_mutex_lock(&philo->data->print);
			philo->data->philo_death = 1;
			printf("%d\n", philo->data->end_program);
			break ;
		}
		print_state(philo, EATING);
		usleep(philo->data->info.time_eat * 1000);
		philo->last_time_eat = philo->data->start_time - get_time();
		philo->times_eat += 1;
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->rigth_fork);
		if (philo->times_eat == philo->data->info.times_must_eat)
		{
			pthread_mutex_lock(&philo->data->print);
			philo->data->all_satisfied += 1;
			break ;
		}
		print_state(philo, SLEEPING);
		usleep(philo->data->info.time_sleep * 1000);
		print_state(philo, THINKING);
	}
	return ;
}

int	rutine_manage(t_philo *philo)
{
	while(1)
	{
		if (philo->data->end_program == 1)
			return (0);
		ft_eat(philo);

	}
	
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
	if (rutine_manage(philo) == 0)
		return (NULL);
	// ft_eat(philo);
	printf("2 --- paso por aqui %zu\n", philo->who);
	// hasta aqui esta bien tengo que gestionar el doctor y demas algo no va bien
	return (NULL);
}
