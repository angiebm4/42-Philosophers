/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doctor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:52:44 by abarrio-          #+#    #+#             */
/*   Updated: 2024/01/07 14:20:23 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// el doctor se va a encarar del seguir el mantenimiento de los filosofos ya que no se
// pueden comunicar entre si

// esto se puede poner en una sola variable en la struct principal y activarla en cuanto uno se muera
// void	*check_death(void *src)
// {
// 	t_data	*data;
// 	size_t	i;

// 	data = src;
// 	i = 0;

// 	while (1)
// 	{
// 		if (data->philo_death == 1)
// 		{
// 			printf("alguien la casco\n");
// 			return (NULL);
// 		}
// 		if ((size_t)data->times_must_eat == data->philo[i].times_eat)
// 			i++;
// 		if (i == data->nb_philo && (size_t)data->times_must_eat == data->philo[data->nb_philo - 1].times_eat)
// 		{
// 			data->end_program = 1;
// 			printf("ya hemos comido todo lo que hay que comer");
			
// 			break ; // ya se han comido todo lo que tienen que comer deberian salir de la simulacion
// 		}
// 	}
// 	while (data->philo_death == 0)
// 		;
// 	return (NULL);
// }


// void	doctor(t_data *data)
// {
// 	pthread_t	doctor;

// 	if (pthread_create(&doctor, NULL, &check_death, data) != 0)
// 	{
// 		perror("Fail thread create\n");
// 		return ;
// 	}
// 	printf("Comenzo el doctor\n");
// }

int	ft_check_death(t_philo *philo)
{
	size_t i;

	i = 0;
	while (i < philo->data->nb_philo)
	{
		if (philo->data->philo_death == 1)
		{
			printf("alguien la casco\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_check_satisfied(t_philo *philo)
{
	size_t i;
	size_t	count_satis_philos;

	i = 0;
	count_satis_philos = 0;
	while (i < philo->data->nb_philo)
	{
		if (count_satis_philos == (size_t)philo->data->times_must_eat)
		{
			printf("ya hemos comido todo lo que hay que comer");
			return (1);
		}
		else if (philo->data->philo[i].times_eat == (size_t)philo->data->times_must_eat)
		{
			count_satis_philos += 1;
			i++;
		}
		else
			break ;
	}
	return (0);
}

int	doctor(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->doctor);
	if ((get_time() - philo->last_time_eat) < philo->data->time_die)
		philo->data->philo_death = 1;
	if (ft_check_death(philo) == 1)
		return (1);
	if (philo->data->times_must_eat != -1)
	{
		if (philo->data->times_must_eat == 0)
		{
			printf("bro no tenemos que comer\n");
			return (1);
		}
		if (ft_check_satisfied(philo) == 1)
			return (1);
	}
	pthread_mutex_unlock(&philo->data->doctor);
	return (0);
}