/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:36:42 by mkling            #+#    #+#             */
/*   Updated: 2025/01/13 11:17:58 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Returns number of miliseconds since 1st january 1970, or 0 if fails */
size_t	get_miliseconds(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		printf("Failed to get the time through gettimeofday");
		return (0);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

size_t	get_actual_time(void)
{
	static int	start_time;

	if (start_time == 0)
		start_time = get_miliseconds();
	return (get_miliseconds() - start_time);
}

void	micro_usleep(size_t wait_time, t_waiter *waiter)
{
	size_t	start;
	size_t	elapsed;
	size_t	remaining;

	start = get_miliseconds();
	while (get_miliseconds() - start < wait_time)
	{
		if (dinner_has_ended(waiter))
			break ;
		elapsed = get_miliseconds() - start;
		remaining = wait_time - elapsed;
		if (remaining > 1000)
			usleep(wait_time / 2);
		else
		{
			while (get_miliseconds() - start < wait_time)
				;
		}
	}
}

void	wait_until_philo_are_seated(t_waiter *waiter)
{
	while (getter(&waiter->table_mutex, &waiter->is_ready) == false)
		;
}
