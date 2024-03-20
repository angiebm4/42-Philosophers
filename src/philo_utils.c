/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:26:59 by abarrio-          #+#    #+#             */
/*   Updated: 2024/03/20 20:03:43 by angela           ###   ########.fr       */
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
	if (nb > INT_MAX)
		data->error = ERROR_INVALID_ARGS;
	return (nb);
}

void	clean_trash(t_data *data)
{
	size_t	i;

	i = 0;
	while (data->forks && i < data->info.nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	if (data->forks)
		free(data->forks);
	pthread_mutex_destroy(&data->print);
	if (data->philo)
		free(data->philo);
	if (data)
		free(data);
}

int	print_error(t_data *data)
{
	if (data->error == ERROR_INVALID_ARGS)
	{
		printf("%sINVALID ARGS%s\n", ORANGE, CLEAR);
		printf("%sPlease follow the followig format:%s\n", ORANGE, CLEAR);
		printf("./philo number_of_philosophers time_to_die time_to_eat ");
		printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		printf("%s---> Only positive numbers are allowed%s\n", ORANGE, CLEAR);
		printf("%s---> Range of numbers go of 0 to INT_MAX%s\n", ORANGE, CLEAR);
		printf("%s---> Time is measured in milliseconds%s\n", ORANGE, CLEAR);
		printf("%s---> The last argument is optional%s\n", ORANGE, CLEAR);
	}
	else if (data->error == ERROR_MALLOC)
		printf("%sMEMORY ERROR%s\n", ORANGE, CLEAR);
	else if (data->error == ERROR_MUTEX)
		printf("%sMUTEX INIT ERROR%s\n", ORANGE, CLEAR);
	else if (data->error == ERROR_CREATE_THREAD)
		printf("%sCREATE THREAD ERROR%s\n", ORANGE, CLEAR);
	else if (data->error == ERROR_JOIN_THREAD)
		printf("%sJOIN THREAD ERROR%s\n", ORANGE, CLEAR);
	clean_trash(data);
	return (1);
}

/* TODO: hacerme mi propia funcion usleep por que lo dice luis y luis es dios*/

size_t	get_time(void)
{
	struct timeval t_time;
	size_t	time_ms;

	gettimeofday(&t_time, NULL);
	time_ms = (t_time.tv_sec * 1000) + (t_time.tv_usec / 1000);
	return(time_ms);
}

void	print_state(t_philo *philo, int state)
{
	size_t	ms;

	ms = get_time() - philo->data->start_time;
	/*if (philo->data->end_program == 1)
		return ;*/
	pthread_mutex_lock(&philo->data->print);
	if (philo->data->end_program == 1)
	{
		pthread_mutex_unlock(&philo->data->print);
		return ;
	}
	if (state == TAKING_A_FORK_L)
		printf("%s%zu ms %zu has taken his left fork\n%s", GREEN, ms, philo->who, CLEAR);
	if (state == TAKING_A_FORK_R)
		printf("%s%zu ms %zu has taken his rigth fork\n%s", GREEN, ms, philo->who, CLEAR);
	if (state == THINKING)
		printf("%s%zu ms %zu is thinking\n%s", YELLOW, ms, philo->who, CLEAR);
	if (state == EATING)
		printf("%s%zu ms %zu is eating\n%s", ORANGE, ms, philo->who, CLEAR);
	if (state == SLEEPING)
		printf("%s%zu ms %zu is sleeping\n%s", BLUE, ms, philo->who, CLEAR);
	if (state == DEATH)
		printf("%s%zu ms %zu died\n%s", RED, ms, philo->who, CLEAR);
	pthread_mutex_unlock(&philo->data->print);
}

