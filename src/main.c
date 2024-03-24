/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:15:56 by abarrio-          #+#    #+#             */
/*   Updated: 2024/03/24 12:30:49 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


void	print_struct(t_data *data)
{
	size_t	i;
	
	i = 0;
	printf(BLUE);
	printf("----- DATA -----\n");
	printf("nb_philo --- %zu\n", data->info.nb_philo);
	printf("time_die --- %zu\n", data->info.time_die);
	printf("time_eat --- %zu\n", data->info.time_eat);
	printf("time_sleep --- %zu\n", data->info.time_sleep);
	printf("times_must_eat --- %d\n", data->info.times_must_eat);
	printf(MAGENTA);
	while (i < data->info.nb_philo)
	{
		printf("pointer to philo %ld --- %p\n", i + 1, &data->philo[i]);
		// printf("----- DATA PHILO %lu -----\n", i + 1);
		i++;
	}
	printf(GREEN);
	printf("start_time --- %ld\n", data->start_time);
	printf("init_program flag --- %d\n", data->init_program);
	printf("end_program flag --- %d\n", data->end_program);
	printf(CLEAR);
}

void	print_philo_data(t_philo *philo)
{
	printf(MAGENTA);
	// printf("----- DATA PHILO -----\n");
	printf("pointer to data struct --- %p\n", philo->data);
	printf("thread id --- %zu\n", philo->thread_id);
	printf("who --- %ld\n", philo->who);
	printf("times eat --- %d\n", philo->times_eat);
	printf("last time eat --- %ld\n", philo->last_time_eat);
	printf("rigth fork --- %p\n", philo->rigth_fork);
	printf("left fork --- %p\n", philo->left_fork);
	printf(CLEAR);
}

void	leaks()
{
	system("leaks -q philo");
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	// atexit(leaks);
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	init_data(data, argc, argv);
	print_struct(data);
	start_simulation(data);
	wait_threads(data);
	/*size_t i = 0;
	while (i < data->info.nb_philo)
	{
		printf("----- DATA PHILO %lu -----\n", i + 1);
		print_philo_data(&data->philo[i]);
		i++;
	}*/
	print_struct(data);
	clean_trash(data);
	return (0);
}
