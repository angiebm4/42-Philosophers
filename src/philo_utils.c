/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:26:59 by abarrio-          #+#    #+#             */
/*   Updated: 2024/03/24 11:28:52 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	philo_atoi(char *str, t_data *data)
{
	// los numeros muy grandes no los gestionas pon un limite a algun numero
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
	if (nb > INT_MAX)
		data->error = ERROR_INVALID_ARGS;
	return (nb);
}

size_t	get_time(void)
{
	struct timeval t_time;
	size_t	time_ms;

	gettimeofday(&t_time, NULL);
	time_ms = (t_time.tv_sec * 1000) + (t_time.tv_usec / 1000);
	return(time_ms);
}



void	clean_trash(t_data *data)
{
	size_t	i;

	i = 0;
	while (data->forks && i < data->info.nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	if (data->forks)
		free(data->forks);
	// pthread_mutex_destroy(&data->print);
	if (data->philo)
		free(data->philo);
	if (data)
		free(data);
}

int	print_error(t_data *data)
{
	if (data->error == ERROR_INVALID_ARGS)
	{
		printf("%sINVALID ARGS%s\n", ORANGE, CLEAR);
		printf("%sPlease follow the followig format:%s\n", ORANGE, CLEAR);
		printf("./philo number_of_philosophers time_to_die time_to_eat ");
		printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		printf("%s---> Only positive numbers are allowed%s\n", ORANGE, CLEAR);
		printf("%s---> Range of numbers go of 0 to INT_MAX%s\n", ORANGE, CLEAR);
		printf("%s---> Time is measured in milliseconds%s\n", ORANGE, CLEAR);
		printf("%s---> The last argument is optional%s\n", ORANGE, CLEAR);
	}
	else if (data->error == ERROR_MALLOC)
		printf("%sMEMORY ERROR%s\n", ORANGE, CLEAR);
	else if (data->error == ERROR_MUTEX)
		printf("%sMUTEX INIT ERROR%s\n", ORANGE, CLEAR);
	else if (data->error == ERROR_CREATE_THREAD)
		printf("%sCREATE THREAD ERROR%s\n", ORANGE, CLEAR);
	else if (data->error == ERROR_JOIN_THREAD)
		printf("%sJOIN THREAD ERROR%s\n", ORANGE, CLEAR);
	clean_trash(data);
	return (1);
}

uint64_t	time_get_msec(uint64_t start)
{
	uint64_t		ret;
	struct timeval	time;

	gettimeofday(&time, NULL);
	ret = time.tv_sec * 1000;
	ret += time.tv_usec / 1000;
	ret -= start;
	return (ret);
}

void	ft_usleep(uint64_t miliseconds)
{
	uint64_t	start;

	start = time_get_msec(0);
	while (time_get_msec(start) < miliseconds)
		usleep(1);
}