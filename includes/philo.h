/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:16:02 by abarrio-          #+#    #+#             */
/*   Updated: 2024/04/25 17:51:11 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "color.h"
# include "default_libs.h"

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
# define LET_FORKS 7

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;
typedef struct s_info	t_info;
typedef struct s_fork	t_fork;

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

	/* PRINT MANAGE MUTEX */
	pthread_mutex_t		print;

	/* DOCTOR */
	pthread_t			doctor;

	/* TIME MANAGE */
	size_t				start_time;
	int					init_program;
	pthread_mutex_t		start_mutex;

	/* FORKS */
	t_fork				*forks;

	pthread_mutex_t		mutex_manage;
	int					end_program;
};

struct					s_fork
{
	pthread_mutex_t		mutex_fork;
	int					fork;
};

struct					s_philo
{
	/* GENERAL DATA */
	t_data				*data;

	/* ID THREAD */
	pthread_t			thread_id;

	/* NB OF PHILO */
	size_t				who;

	/* END FLAGS DOCTORSITO */
	pthread_mutex_t		philo_manage;
	int					satisfied;
	int					flag;

	/* EAT STATS */
	size_t				last_time_eat;
	int					times_eat;

	/* FORKS */
	t_fork				*rigth_fork;
	t_fork				*left_fork;
};

/* INIT STRUCT */
void					init_data(t_data *data, int argc, char *argv[]);

/* UTILS */
size_t					philo_atoi(char *str, t_data *data);
int						print_error(t_data *data);
void					clean_trash(t_data *data);
void					print_state(t_philo *philo, int state);

/* TIME MANAGE */
size_t					get_time(void);
void					ft_usleep(size_t time);

/* PHILOS RUTINE */
void					*rutine(void *src);
int	end_pthread(t_philo *philo);

/* RUTINE HABITS */
int						ft_eat(t_philo *philo);
void					ft_sleep(t_philo *philo);
void					ft_thinking(t_philo *philo);

/* START SIMULATION */
void					start_simulation(t_data *data);
void					wait_threads(t_data *data);

/* DOCTOR MANAGE */
int						doctor_manage(t_data *data);

#endif