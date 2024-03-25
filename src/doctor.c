/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doctor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:45:41 by abarrio-          #+#    #+#             */
/*   Updated: 2024/03/25 12:31:36 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*doc_rutine(void *src)
{
	t_data	*data;

	data = (t_data*)src;
    
    while (1)
    {
        pthread_mutex_lock(&data->start_mutex);
        if (data->init_program == 0)
        {
            pthread_mutex_unlock(&data->start_mutex);
            break;
        }
        pthread_mutex_unlock(&data->start_mutex);
    }
    
    size_t  i;
    size_t all_satis = 0;
    while (1)
    {
        i = 0;
        while (i < data->info.nb_philo)
        {
            pthread_mutex_lock(&data->philo[i].philo_manage);
            if (data->philo[i].die)
            {
                pthread_mutex_lock(&data->mutex_manage);
                data->end_program = 1;
                pthread_mutex_unlock(&data->mutex_manage);
                pthread_mutex_unlock(&data->philo[i].philo_manage);
                return (NULL);
            }
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
        {
            pthread_mutex_lock(&data->mutex_manage);
            data->end_program = 1;
            pthread_mutex_unlock(&data->mutex_manage);
            return (NULL);
        }
    }
    return (NULL);
    
    
    /*pthread_mutex_lock(&data->mutex_manage);
    printf("%s DCOTROSITOO LABURANDOOO %s\n", RED, CLEAR);
    ft_usleep(1);
    data->end_program = 1;
    
    pthread_mutex_lock(&data->print);
    printf("%s ----- %d ----- %s\n", RED, data->end_program, CLEAR);
    pthread_mutex_unlock(&data->print);
    pthread_mutex_unlock(&data->mutex_manage);*/
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