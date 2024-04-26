/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:39:58 by abarrio-          #+#    #+#             */
/*   Updated: 2024/04/26 11:05:00 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	get_instant(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

void	ft_usleep(size_t time)
{
	size_t	begin;

	begin = get_instant();
	while (get_instant() - begin < time)
		usleep(200);
}

size_t	get_time(void)
{
	struct timeval	t_time;
	size_t			time_ms;

	gettimeofday(&t_time, NULL);
	time_ms = (t_time.tv_sec * 1000) + (t_time.tv_usec / 1000);
	return (time_ms);
}
