/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:07:34 by abarrio-          #+#    #+#             */
/*   Updated: 2024/01/04 11:38:13 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "default_libs.h"
# include "color.h"

# define ERROR_INVALID_ARGS 1


typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

struct					s_data
{
	t_philo				*philo;
	size_t				nb_philo;
	size_t				forks_to_eat;
	pthread_mutex_t		mutex;
	// time medido en milisegundos
	size_t				time_die;
	size_t				time_eat;
	size_t				time_sleep;
	size_t				times_must_eat;
	int					error;
};

struct					s_philo
{
	pthread_t			thread;
	t_data				*data;
};

#endif