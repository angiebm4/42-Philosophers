/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:07:37 by abarrio-          #+#    #+#             */
/*   Updated: 2024/01/04 11:38:44 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	philo_atoi(char *str, t_data *data)
{
	int		i;
	size_t	nb;

	nb = 0;
	i = 0;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
	{
		data->error = ERROR_INVALID_ARGS;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = ((str[i] - '0') + (nb * 10));
		i++;
	}
	if (str[i] != '\0')
	{
		data->error = ERROR_INVALID_ARGS;
		i++;
	}
	return (nb);
}

void	print_error(t_data *data)
{
	if (data->error == 1)
	{
		printf("%sINVALID ARGS%s\n", ORANGE, CLEAR);
		printf("%sPlease follow the followig format:%s\n", ORANGE, CLEAR);
		printf("./philo number_of_philosophers time_to_die time_to_eat ");
		printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		printf("%s---> Only positive numbers are allowed%s\n", ORANGE, CLEAR);
		printf("%s---> Time is measured in milliseconds%s\n", ORANGE, CLEAR);
		printf("%s---> The last argument is optional%s\n", ORANGE, CLEAR);
		
	}
	return ;
}

void	init_data(t_data *data, int argc, char *argv[])
{
	memset(data, 0, sizeof(t_data));
	if (argc < 5 || argc > 6)
	{
		data->error = ERROR_INVALID_ARGS;
		return ;
	}
	data->nb_philo = philo_atoi(argv[1], data);
	data->time_die = philo_atoi(argv[2], data);
	data->time_eat = philo_atoi(argv[3], data);
	data->time_sleep = philo_atoi(argv[4], data);
	if (argv[5])
		data->times_must_eat = philo_atoi(argv[5], data);
	else
		data->times_must_eat = -1; //infinito hasta que muera un philosofer
	data->philo = malloc(data->nb_philo * sizeof(t_philo)); // acordarse de liberar cosas
	if (!data->philo)
		return ; // errorr malloc
}

void	*rutine()
{
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	size_t	i;

	init_data(&data, argc, argv);
	pthread_mutex_init(&data.mutex, NULL);
	i = 0;
	if (data.error == 1)
	{
		print_error(&data);
		return (0);
	}
	// no hay que empezar a ejecutar el programa hasta qe todos los hilos se han creado
	// un mutex para que cuando un philo escriba no puedan escribir el resto
	// tener en cuenta
	while (i < data.nb_philo)
	{
		data.philo[i].data = &data;
		if (pthread_create(&data.philo[i].thread, NULL, &rutine, NULL) != 0)
		// routine es una funcion a la que va el hilo
		{
			perror("Fail thread create\n");
			return (0);
		}
		i++;
		printf("Comenzo el %ld philosofo\n", i);
	}
	i = 0;
	while (i < data.nb_philo)
	{
		if (pthread_join(data.philo[i].thread, NULL) != 0)
		// esperar a que acabe cada philosofo si uno muere todos acaban
			return (0);
		i++;
		printf("Termino el %ld philosofo\n", i);
	}
	pthread_mutex_destroy(&data.mutex);
	return (0);
}
