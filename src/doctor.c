/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doctor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:52:44 by abarrio-          #+#    #+#             */
/*   Updated: 2024/01/06 22:02:54 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// el doctor se va a encarar del seguir el mantenimiento de los filosofos ya que no se
// pueden comunicar entre si

// esto se puede poner en una sola variable en la struct principal y activarla en cuanto uno se muera
void	*check_death(void *src)
{
	t_data	*data;
	size_t	i;

	data = src;
	i = 0;

	while (1)
	{
		if (data->philo_death == 1)
		{
			printf("alguien la casco\n");
			return (NULL);
		}
		if (data->times_must_eat == data->philo[i].times_eat)
			i++;
		if (i == data->nb_philo && data->times_must_eat == data->philo[data->nb_philo - 1].times_eat)
		{
			printf("ya hemos comido todo lo que hay que comer");
			break ; // ya se han comido todo lo que tienen que comer deberian salir de la simulacion
		}
	}
	while (data->philo_death == 0)
		;
	return (NULL);
}

void	doctor(t_data *data)
{
	pthread_t	doctor;

	if (pthread_create(&doctor, NULL, &check_death, data) != 0)
	{
		perror("Fail thread create\n");
		return ;
	}
	printf("Comenzo el doctor\n");
}