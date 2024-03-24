/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:05:27 by abarrio-          #+#    #+#             */
/*   Updated: 2024/03/24 18:48:17 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*rutine(void *src)
{
    t_philo	*philo;

	philo = (t_philo*)src;
    pthread_mutex_lock(&philo->data->print);
    print_philo_data(philo);
    pthread_mutex_unlock(&philo->data->print);
    
    while (1)
    {
        pthread_mutex_lock(&philo->data->start_mutex);
        if (philo->data->init_program == 0)
        {
            pthread_mutex_unlock(&philo->data->start_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->data->start_mutex);
    }
    
    pthread_mutex_lock(&philo->data->print);
    printf("estoy preparado para comenzar %ld\n", philo->who);
    ft_usleep(10);
    pthread_mutex_unlock(&philo->data->print);
    while(1)
    {
        pthread_mutex_lock(&philo->data->mutex_manage);
        pthread_mutex_lock(&philo->data->print);
        printf("%s -- %d -- %s\n", GREEN, philo->data->end_program, CLEAR);
        pthread_mutex_unlock(&philo->data->print);
        if (philo->data->end_program == 1)
        {
            pthread_mutex_lock(&philo->data->print);
            printf("%s ME OBLIGARON A TERMINAR %ld\n%s", RED, philo->who, CLEAR);
            pthread_mutex_unlock(&philo->data->print);
            pthread_mutex_unlock(&philo->data->mutex_manage);
            return (NULL);
        }
        pthread_mutex_unlock(&philo->data->mutex_manage);
        pthread_mutex_lock(&philo->data->print);
        printf("laburando uwu %ld\n", philo->who);
        pthread_mutex_unlock(&philo->data->print);
        ft_usleep(2000);
        pthread_mutex_lock(&philo->data->mutex_manage);
        philo->times_eat += 1;
        pthread_mutex_unlock(&philo->data->mutex_manage);
        
    }
    return (NULL);
}