/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doctor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:45:41 by abarrio-          #+#    #+#             */
/*   Updated: 2024/03/20 19:45:47 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* TODO: esto esta mal se queda en buble por el doctorsito ademas de que no hay condicion para parar todos losfilos*/
void	*doc_rutine(void *src)
{
	t_data	*data;
	size_t		i;

	data = (t_data*)src;
	while (1)
	{
		pthread_mutex_lock(&data->mutex_manage);
		i = 0;
		if (data->all_satisfied == data->info.nb_philo)
		{
			data->end_program = 1;
			pthread_mutex_unlock(&data->mutex_manage);
			return (NULL);
		}
		while(i < data->info.nb_philo)
		{
			pthread_mutex_lock(&data->philo[i].mutex_philo);
			if (data->philo[i].die == 1)
			{
				data->end_program = 1;
				pthread_mutex_unlock(&data->mutex_manage);
				pthread_mutex_unlock(&data->philo[i].mutex_philo);
				return (NULL);
			}
			pthread_mutex_unlock(&data->philo[i].mutex_philo);
			i++;
		}
	}
	return (NULL);
}

int	doctor(t_data *data)
{
	if (pthread_create(&data->doctor, NULL, &doc_rutine, &data))
	{
		data->error = ERROR_CREATE_THREAD;
		return (1);
	}
	return (0);
}
