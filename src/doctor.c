/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doctor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:45:41 by abarrio-          #+#    #+#             */
/*   Updated: 2024/03/24 14:03:12 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*doc_rutine(void *src)
{
	t_data	*data;

	data = (t_data*)src;
    while (data->init_program == 1)
		ft_usleep(1);
    pthread_mutex_lock(&data->print);
    printf("%s DCOTROSITOO LABURANDOOO %s\n", RED, CLEAR);
    pthread_mutex_unlock(&data->print);
    ft_usleep(5000);
    pthread_mutex_lock(&data->mutex_manage);
    printf("%s DCOTROSITOO LABURANDOOO %s\n", RED, CLEAR);
    ft_usleep(1);
    data->end_program = 1;
    pthread_mutex_lock(&data->print);
    printf("%s ----- %d ----- %s\n", RED, data->end_program, CLEAR);
    pthread_mutex_unlock(&data->print);
    pthread_mutex_unlock(&data->mutex_manage);
	return (NULL);
}

int	doctor_manage(t_data *data)
{
	if (pthread_create(&data->doctor, NULL, &doc_rutine, &data))
	{
		data->error = ERROR_CREATE_THREAD;
		return (1);
	}
	return (0);
}