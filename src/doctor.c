/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doctor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:45:41 by abarrio-          #+#    #+#             */
/*   Updated: 2024/04/19 14:24:59 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*all_philo_satis(t_data *data)
{
	pthread_mutex_lock(&data->mutex_manage);
	data->end_program = 1;
	pthread_mutex_unlock(&data->mutex_manage);
	return (NULL);
}

void	*someone_die(t_data *data, int i)
{
	size_t	ms;

	ms = get_time() - data->start_time;
	pthread_mutex_lock(&data->mutex_manage);
	data->end_program = 1;
	pthread_mutex_unlock(&data->mutex_manage);
	pthread_mutex_lock(&data->print);
	printf("%s%zu ms %zu died\n%s", RED, ms, data->philo[i].who, CLEAR);
	pthread_mutex_unlock(&data->print);
	pthread_mutex_unlock(&data->philo[i].philo_manage);
	return (NULL);
}

void	*check_philo_stats(t_data *data, size_t all_satis)
{
	size_t	i;

	while (1)
	{
		i = 0;
		while (i < data->info.nb_philo)
		{
			pthread_mutex_lock(&data->philo[i].philo_manage);
			if (data->info.time_die < get_time() - data->philo[i].last_time_eat)
				return (someone_die(data, i));
			pthread_mutex_unlock(&data->philo[i].philo_manage);
			pthread_mutex_lock(&data->philo[i].philo_manage);
			if (data->philo[i].satisfied == 1 && data->philo[i].flag == 0)
			{
				all_satis++;
				data->philo[i].flag = 1;
			}
			pthread_mutex_unlock(&data->philo[i].philo_manage);
			i++;
		}
		if (all_satis == data->info.nb_philo)
			return (all_philo_satis(data));
	}
}

void	*doc_rutine(void *src)
{
	t_data	*data;

	data = (t_data *)src;
	while (1)
	{
		pthread_mutex_lock(&data->start_mutex);
		if (data->init_program == 0)
		{
			pthread_mutex_unlock(&data->start_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->start_mutex);
	}
	return (check_philo_stats(data, 0));
}

int	doctor_manage(t_data *data)
{
	if (pthread_create(&data->doctor, NULL, &doc_rutine, data))
	{
		data->error = ERROR_CREATE_THREAD;
		return (1);
	}
	return (0);
}
