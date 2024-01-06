/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:07:34 by abarrio-          #+#    #+#             */
/*   Updated: 2024/01/06 20:23:56 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "default_libs.h"
# include "color.h"

# define ERROR_INVALID_ARGS 1

// state of the philosofer
# define TAKING_A_FORK 1
# define EATING 2
# define SLEEPING 3
# define THINKING 4
# define DEATH 5

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

struct					s_data
{
	t_philo				*philo;
	size_t				nb_philo;
	pthread_mutex_t		*forks;
	pthread_mutex_t		mutex;
	pthread_mutex_t		print;
	size_t				start_time; // inicializarlo
	// time medido en milisegundos
	size_t				time_die;
	size_t				time_eat;
	size_t				time_sleep;
	size_t				times_must_eat;
	int					error;
	int					init_program;
	int					philo_death; // 1 si 0 no
};

struct					s_philo
{
	pthread_t			thread_id;
	size_t				who; // inicializarlo
	t_data				*data;
	size_t				times_eat;
	size_t				last_time_eat;
	pthread_mutex_t		*rigth_fork; //que tipo de variable tiene que ser ?
	pthread_mutex_t		*left_fork;
};

// philo utils
size_t	philo_atoi(char *str, t_data *data);
size_t	get_time(void);

// init variables
void	assign_forks(t_data *data);
void	assing_who(t_data *data);
void	init_data(t_data *data, int argc, char *argv[]);

// print msgs
void	print_error(t_data *data);
void	print_state(t_philo *philo, int state);

// doctor 
int	check_death(t_data *data);

// rutine
void	*rutine(void *src);

#endif