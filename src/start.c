/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:43:58 by abarrio-          #+#    #+#             */
/*   Updated: 2024/04/09 16:32:45 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	wait_threads(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->info.nb_philo)
	{
		if (pthread_join(data->philo[i].thread_id, NULL) != 0)
		{
			data->error = ERROR_JOIN_THREAD;
			return ;
		}
		i++;
	}
	if (pthread_join(data->doctor, NULL) != 0)
	{
		data->error = ERROR_JOIN_THREAD;
		return ;
	}
}

void	start_simulation(t_data *data)
{
	size_t	i;

	i = 0;
	if (doctor_manage(data) == 1)
		return ;
	while (i < data->info.nb_philo)
	{
		data->philo[i].data = data;
		if (pthread_create(&data->philo[i].thread_id, NULL, &rutine,
				&data->philo[i]) != 0)
		{
			data->error = ERROR_CREATE_THREAD;
			return ;
		}
		i++;
	}
	data->start_time = get_time();
	i = -1;
	while (++i < data->info.nb_philo)
		data->philo[i].last_time_eat = data->start_time;
	pthread_mutex_lock(&data->start_mutex);
	data->init_program = 0;
	pthread_mutex_unlock(&data->start_mutex);
}
