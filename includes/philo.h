/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:16:02 by abarrio-          #+#    #+#             */
/*   Updated: 2024/01/22 10:00:11 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H

# include "default_libs.h"
# include "color.h"

# define ERROR_INVALID_ARGS 1
# define ERROR_MALLOC 2
# define ERROR_MUTEX 3
# define ERROR_CREATE_THREAD 4
# define ERROR_JOIN_THREAD 5

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
	//philo
	t_philo				*philo;
	// args
	size_t				nb_philo;
	size_t				time_die;
	size_t				time_eat;
	size_t				time_sleep;
	int					times_must_eat;
	// error flag
	int					error;
	// mutex
	pthread_mutex_t		*forks;
	pthread_mutex_t		print;
	// doctor
	pthread_t			doctor;
	// time manage
	size_t				start_time;
	int					init_program;
	int					end_program;
	// end flag
	int					philo_death; // 1 si 0 no
	size_t				all_satisfied;
};

struct					s_philo
{
	t_data				*data;
	pthread_t			thread_id;
	size_t				who;
	size_t				last_time_eat;
	int				times_eat;
	pthread_mutex_t		*rigth_fork;
	pthread_mutex_t		*left_fork;
};

// utils
size_t	philo_atoi(char *str, t_data *data);
int		print_error(t_data *data);
void	print_state(t_philo *philo, int state);
void	clean_trash(t_data *data);
size_t	get_time(void);

// init struct
void	init_data(t_data *data, int argc, char *argv[]);
void	init_philo(t_data *data);

//simulation start 
void 	start_simulation(t_data *data);
void	wait_threads(t_data *data);

// rutine 
void	*rutine(void *src);

// borrar luag
void	print_struct(t_data *data);

// // doctor
int	doctor(t_data *data);
void	*doc_rutine(void *src);

#endif