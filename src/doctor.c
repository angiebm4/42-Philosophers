/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doctor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:45:41 by abarrio-          #+#    #+#             */
/*   Updated: 2024/03/08 20:23:07 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* TODO: esto esta mal se queda en buble por el doctorsito ademas de que no hay condicion para parar todos losfilos*/
void	*doc_rutine(void *src)
{
	t_data	*data;

	data = (t_data*)src;
	while (1)
	{
		// printf("el doctor esta labuarando\n");
		if (data->philo_death == 1 || data->all_satisfied == data->info.nb_philo)
		{
			printf("el doctor detecto que te moriste\n");
			pthread_mutex_lock(&data->print);
			data->end_program = 1;
			pthread_mutex_unlock(&data->print);
			break ;
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
