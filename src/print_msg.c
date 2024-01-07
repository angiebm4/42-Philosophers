/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:16:49 by abarrio-          #+#    #+#             */
/*   Updated: 2024/01/07 15:12:52 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_error(t_data *data)
{
	if (data->error == 1)
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
	return ;
}

void	print_state(t_philo *philo, int state)
{
	size_t	ms;

	ms = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print);
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
