/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:07:34 by abarrio-          #+#    #+#             */
/*   Updated: 2024/01/07 15:12:19 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "default_libs.h"
# include "color.h"

# define ERROR_INVALID_ARGS 1

// state of the philosofer
# define TAKING_A_FORK_R 1
# define TAKING_A_FORK_L 2
# define EATING 3
# define SLEEPING 4
# define THINKING 5
# define DEATH 6

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

struct					s_data
{
	t_philo				*philo;
	size_t				nb_philo;
	pthread_mutex_t		*forks;
	pthread_mutex_t		mutex;
	pthread_mutex_t		print;
	pthread_mutex_t		doctor; // si la funcion devuekve 1 se acabo el programa si devuelve 0 sigue el programa
	size_t				start_time;
	// time medido en milisegundos
	size_t				time_die;
	size_t				time_eat;
	size_t				time_sleep;
	int					times_must_eat;
	size_t				all_satisfied;
	int					error;
	int					init_program;
	int					philo_death; // 1 si 0 no
	int					end_program;
};

struct					s_philo
{
	pthread_t			thread_id;
	size_t				who;
	t_data				*data;
	size_t				times_eat;
	size_t				last_time_eat;
	pthread_mutex_t		*rigth_fork;
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
int		doctor(t_philo *philo);

// rutine
void	*rutine(void *src);

#endif