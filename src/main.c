/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:15:56 by abarrio-          #+#    #+#             */
/*   Updated: 2024/04/21 15:05:55 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*void	leaks(void)
{
	system("leaks -q philo");
}*/

int	main(int argc, char *argv[])
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	init_data(data, argc, argv);
	if (data->error != 0)
		return (print_error(data));
	start_simulation(data);
	if (data->error != 0)
		return (print_error(data));
	wait_threads(data);
	if (data->error != 0)
		return (print_error(data));
	clean_trash(data);
	return (0);
}
