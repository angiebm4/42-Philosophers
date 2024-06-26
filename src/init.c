/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:40:51 by abarrio-          #+#    #+#             */
/*   Updated: 2024/04/11 12:05:42 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	assign_forks(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->info.nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i].mutex_fork, NULL) == -1)
			data->error = ERROR_MUTEX;
		data->forks[i].fork = 0;
		i++;
	}
	i = 0;
	while (i < data->info.nb_philo)
	{
		data->philo[i].rigth_fork = &data->forks[i];
		data->philo[i].left_fork = &data->forks[(i + 1) % data->info.nb_philo];
		i++;
	}
}

void	init_philo(t_data *data)
{
	size_t	i;

	(data->philo) = malloc(data->info.nb_philo * (sizeof(t_philo)));
	if (!data->philo)
	{
		data->error = ERROR_MALLOC;
		return ;
	}
	memset(data->philo, 0, (sizeof(t_philo)) * data->info.nb_philo);
	i = 0;
	while (i < data->info.nb_philo)
	{
		data->philo[i].who = i + 1;
		if (pthread_mutex_init(&data->philo[i].philo_manage, NULL) == -1)
			data->error = ERROR_MUTEX;
		i++;
	}
	assign_forks(data);
}

void	mutex_init(t_data *data)
{
	if (pthread_mutex_init(&data->print, NULL) == -1)
		data->error = ERROR_MUTEX;
	if (pthread_mutex_init(&data->mutex_manage, NULL) == -1)
		data->error = ERROR_MUTEX;
	if (pthread_mutex_init(&data->start_mutex, NULL) == -1)
		data->error = ERROR_MUTEX;
}

void	init_data(t_data *data, int argc, char *argv[])
{
	memset(data, 0, (sizeof(t_data)));
	if (argc < 5 || argc > 6)
	{
		data->error = ERROR_INVALID_ARGS;
		return ;
	}
	mutex_init(data);
	data->init_program = 1;
	data->info.nb_philo = philo_atoi(argv[1], data);
	data->info.time_die = philo_atoi(argv[2], data);
	data->info.time_eat = philo_atoi(argv[3], data);
	data->info.time_sleep = philo_atoi(argv[4], data);
	if (argv[5])
		data->info.times_must_eat = (int)philo_atoi(argv[5], data);
	else
		data->info.times_must_eat = -1;
	data->forks = malloc(data->info.nb_philo * sizeof(t_fork));
	if (!data->forks)
	{
		data->error = ERROR_MALLOC;
		return ;
	}
	init_philo(data);
}
