/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:43:58 by abarrio-          #+#    #+#             */
/*   Updated: 2024/01/17 12:47:52 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	wait_threads(t_data *data)
{
	size_t i;

	// hay que ver cual es la diferencia entre el threat join y el pthread_detach
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(data->philo[i].thread_id, NULL) != 0)
		{
			data->error = ERROR_JOIN_THREAD;
			// esperar a que acabe cada philosofo si uno muere todos acaban
			return ;
		}
		i++;
		printf("Termino el %ld philosofo\n", i);
	}
	if (pthread_join(data->doctor, NULL) != 0)
	{
		data->error = ERROR_JOIN_THREAD;
		// esperar a que acabe cada philosofo si uno muere todos acaban
		return ;
	}
}

void start_simulation(t_data *data)
{
	size_t	i;

	i = 0;
	if (doctor(data) == 1)
		return ;
	while (i < data->nb_philo)
	{
		data->philo[i].data = data;
		if (pthread_create(&data->philo[i].thread_id, NULL, &rutine, &data->philo[i]) != 0)
		{
			data->error = ERROR_CREATE_THREAD;
			return ;
		}
		i++;
		printf("Comenzo el %ld philosofo\n", i);
	}
	data->start_time = get_time();
	i = 0;
	while (i < data->nb_philo)
	{
		data->philo[i].last_time_eat = data->start_time;
		i++;
	}
	data->init_program = 0;
}
