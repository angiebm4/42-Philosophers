/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:05:50 by abarrio-          #+#    #+#             */
/*   Updated: 2024/01/07 15:16:13 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	assign_forks(t_data *data)
{
	size_t		i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		data->philo[i].rigth_fork = &data->forks[i];
		data->philo[i].left_fork = &data->forks[(i + 1) % data->nb_philo];
		i++;
	}
}

void	assing_who(t_data *data)
{
	size_t		i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philo[i].who = i + 1;
		i++;
	}
}
void	init_philo(t_data *data)
{
	size_t i;

	i = 0;
	data->philo = malloc(data->nb_philo * sizeof(t_philo)); // acordarse de liberar cosas
	if (!data->philo)
		return ; // errorr malloc
	while (i < data->nb_philo)
	{
		memset(&data->philo[i], 0, sizeof(t_philo));
		i++;
	}
	assing_who(data);
	assign_forks(data);
}

void	init_data(t_data *data, int argc, char *argv[])
{
	memset(data, 0, sizeof(t_data));
	if (argc < 5 || argc > 6)
	{
		data->error = ERROR_INVALID_ARGS;
		return ;
	}
	data->init_program = 1;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->mutex, NULL);
	pthread_mutex_init(&data->doctor, NULL);
	data->nb_philo = philo_atoi(argv[1], data);
	data->time_die = philo_atoi(argv[2], data);
	data->time_eat = philo_atoi(argv[3], data);
	data->time_sleep = philo_atoi(argv[4], data);
	if (argv[5])
		data->times_must_eat = (int)philo_atoi(argv[5], data);
	else
		data->times_must_eat = -1; //infinito hasta que muera un philosofer
	data->forks = malloc(data->nb_philo * sizeof(pthread_mutex_t*)); // acordarse de liberar cosas
	if (!data->forks)
		return ; // errorr malloc
	init_philo(data);
}
