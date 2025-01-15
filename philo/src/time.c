/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:36:42 by mkling            #+#    #+#             */
/*   Updated: 2025/01/15 21:46:16 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Returns number of miliseconds since 1st january 1970, or 0 if fails */
size_t	get_miliseconds(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

size_t	get_actual_time(t_philo *philo)
{
	return (get_miliseconds() - philo->start_time);
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

/* No need for mutex because applies before routine starts */
int	set_start_time(t_waiter *waiter)
{
	int	i;

	waiter->start_time = get_miliseconds();
	if (waiter->start_time == 0)
		return (print_error(ERR_TIME));
	i = 0;
	while (i < waiter->philo_total)
	{
		waiter->philo_array[i]->last_meal_time = waiter->start_time;
		waiter->philo_array[i++]->start_time = waiter->start_time;
	}
	return (SUCCESS);
}

void	wait_until_philo_are_seated(t_waiter *waiter)
{
	while (getter(&waiter->waiter_mutex, &waiter->is_on) == false)
		;
}
