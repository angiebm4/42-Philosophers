/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doctor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:52:44 by abarrio-          #+#    #+#             */
/*   Updated: 2024/01/06 19:09:36 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// el doctor se va a encarar del seguir el mantenimiento de los filosofos ya que no se
// pueden comunicar entre si

// esto se puede poner en una sola variable en la struct principal y activarla en cuanto uno se muera
int	check_death(t_data *data)
{
	if (data->philo_death == 1)
		exit(0); // no se puede hacer exit
	return (1);
}
