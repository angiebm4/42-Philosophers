/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:39:58 by abarrio-          #+#    #+#             */
/*   Updated: 2024/04/03 23:05:11 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static uint64_t	time_get_msec(uint64_t start)
{
	uint64_t		ret;
	struct timeval	time;

	gettimeofday(&time, NULL);
	ret = time.tv_sec * 1000;
	ret += time.tv_usec / 1000;
	ret -= start;
	return (ret);
}

void	ft_usleep(uint64_t miliseconds)
{
	uint64_t	start;

	start = time_get_msec(0);
	while (time_get_msec(start) < miliseconds)
		usleep(1);
}

size_t	get_time(void)
{
	struct timeval	t_time;
	size_t			time_ms;

	gettimeofday(&t_time, NULL);
	time_ms = (t_time.tv_sec * 1000) + (t_time.tv_usec / 1000);
	return (time_ms);
}
