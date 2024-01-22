/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:15:56 by abarrio-          #+#    #+#             */
/*   Updated: 2024/01/17 12:31:35 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


void	print_struct(t_data *data)
{
	size_t	i;
	
	i = 0;
	printf(BLUE);
	printf("----- DATA -----\n");
	printf("nb_philo --- %zu\n", data->nb_philo);
	printf("time_die --- %zu\n", data->time_die);
	printf("time_eat --- %zu\n", data->time_eat);
	printf("time_sleep --- %zu\n", data->time_sleep);
	printf("times_must_eat --- %d\n", data->times_must_eat);
	printf("flag error --- %d\n", data->error);
	printf("start_time --- %zu\n", data->start_time);
	printf("flag init_program --- %d\n", data->init_program);
	printf(MAGENTA);
	while (i < data->nb_philo)
	{
		printf("----- DATA PHILO %lu -----\n", i + 1);
		printf("who --- %zu\n", data->philo[i].who);
		printf("thread_id --- %p\n", data->philo[i].thread_id);
		printf("rigth_fork --- %p\n", data->philo[i].rigth_fork);
		printf("left_fork --- %p\n", data->philo[i].left_fork);
		i++;
	}
	printf(CLEAR);
}

void	leaks()
{
	system("leaks -q philo");
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	atexit(leaks);
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	init_data(data, argc, argv);
	if (data->error != 0)
		return(print_error(data));
	start_simulation(data);
	if (data->error != 0)
		return(print_error(data));
	wait_threads(data);
	if (data->error != 0)
		return(print_error(data));
	//final
	print_struct(data);
	clean_trash(data);
	return (0);
}
