/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:02:04 by abarrio-          #+#    #+#             */
/*   Updated: 2024/01/07 18:06:36 by abarrio-         ###   ########.fr       */
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

void	ft_clean_trash(t_data *data)
{
	size_t	i;

	i = 0;
	pthread_mutex_destroy(&data->mutex);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->doctor);
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		free(data->philo);
		i++;
	}
}

// void	ft_end_program()
// {
	
// }

