/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:02:04 by abarrio-          #+#    #+#             */
/*   Updated: 2024/01/06 21:40:12 by abarrio-         ###   ########.fr       */
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



