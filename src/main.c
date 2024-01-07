/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:07:37 by abarrio-          #+#    #+#             */
/*   Updated: 2024/01/07 18:07:29 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// void	leaks()
// {
// 	system("leaks -q philo");
// }

int	main(int argc, char *argv[])
{
	t_data	data;
	size_t	i;
	 
	// por algun motivo nunca me termina el programa que coño le pasa aaasdhajfgfvhb
	// controlar los deathlocks ?? realmente esto sucece en mi codigo? 
	// un deathlock es cuando cada filosofo pilla un teneor por lo que se bloquea el 
	// sitema y estan todos esperando a que se desbloquee el otro tenedor pero nunca lo hace 
	// hay que gestionar posibles errores del mutex y de los hilos???????
	// atexit(leaks);
	init_data(&data, argc, argv);
	i = 0;
	if (data.error == 1)
	{
		print_error(&data);
		return (0);
	}
	// no hay que empezar a ejecutar el programa hasta qe todos los hilos se han creado
	// un mutex para que cuando un philo escriba no puedan escribir el resto
	// tener en cuenta
	// mi doctor tiene que ser un hilo a parte como la primera vez que lo hice pero como 
	// mierdas aro la simulacion , se supone que los filosofos no se pueden comunicar entre si pero
	// suppongo que si con el medico mmmmmm
	while (i < data.nb_philo)
	{
		data.philo[i].data = &data;
		if (pthread_create(&data.philo[i].thread_id, NULL, &rutine, &data.philo[i]) != 0)
		// routine es una funcion a la que va el hilo
		{
			perror("Fail thread create\n");
			return (0);
		}
		i++;
		printf("Comenzo el %ld philosofo\n", i);
	}
	data.start_time = get_time();
	data.init_program = 0;
	i = 0;
	while (i < data.nb_philo)
	{
		if (pthread_join(data.philo[i].thread_id, NULL) != 0)
		// esperar a que acabe cada philosofo si uno muere todos acaban
			return (0);
		i++;
		printf("Termino el %ld philosofo\n", i);
	}
	// liberar toda la memria y destruir todos los mutex
	ft_clean_trash(&data);
	return (0);
}
