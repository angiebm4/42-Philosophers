/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:16:02 by abarrio-          #+#    #+#             */
/*   Updated: 2024/03/20 11:27:21 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "default_libs.h"
# include "color.h"

/* ERROR DEFINE */
# define ERROR_INVALID_ARGS 1
# define ERROR_MALLOC 2
# define ERROR_MUTEX 3
# define ERROR_CREATE_THREAD 4
# define ERROR_JOIN_THREAD 5

/* STATE OF THE PHILOSOFER */
# define TAKING_A_FORK_R 1
# define TAKING_A_FORK_L 2
# define EATING 3
# define SLEEPING 4
# define THINKING 5
# define DEATH 6

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;
typedef struct s_info	t_info;

struct					s_info
{
	size_t				nb_philo;
	size_t				time_die;
	size_t				time_eat;
	size_t				time_sleep;
	int					times_must_eat;
};

struct					s_data
{
	/* PHILOS */
	t_philo				*philo;
	
	/* INFO */
	t_info				info;
	
	/* FLAG ERROR */ /* SI DA ERROR ACABAR */
	int					error;
	
	/* FORKS */
	pthread_mutex_t		*forks;

	/* PRINT MANAGE MUTEX */
	pthread_mutex_t		print;
	
	/* DOCTOR */
	pthread_t			doctor;
	
	/* TIME MANAGE */
	size_t				start_time;
	int					init_program;
	int					end_program;
	pthread_mutex_t		mutex_manage;
	
	/* END FLAG */
	int					philo_death; // 1 si 0 no
	size_t				all_satisfied;
};

struct					s_philo
{
	/* GENERAL DATA */
	t_data				*data;
	
	/* ID THREAD */
	pthread_t			thread_id;
	
	/* MUTEX TO CONTROL PHILO INFO */
	pthread_mutex_t		mutex_philo;
	
	/* IM DIE */
	size_t				die;
	
	/* NB OF PHILO */
	size_t				who;

	/* EAT STATS */
	size_t				last_time_eat;
	int					times_eat;

	/* FORKS */
	pthread_mutex_t		*rigth_fork;
	pthread_mutex_t		*left_fork;
};

/* UTILS */
size_t	philo_atoi(char *str, t_data *data);
int		print_error(t_data *data);
void	print_state(t_philo *philo, int state);
void	clean_trash(t_data *data);
size_t	get_time(void);

/* INIT STRUCT */
void	init_data(t_data *data, int argc, char *argv[]);
void	init_philo(t_data *data);

/* START SIMULATION */
void 	start_simulation(t_data *data);
void	wait_threads(t_data *data);

/* PHILOS RUTINE */
void	*rutine(void *src);

/* DEBUGGING: DELETE */
void	print_struct(t_data *data);

/* DOCTOR */
int	doctor(t_data *data);
void	*doc_rutine(void *src);

#endif