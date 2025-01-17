/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:36:42 by mkling            #+#    #+#             */
/*   Updated: 2025/01/17 14:17:35 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Returns number of miliseconds since 1st january 1970, or 0 if fails */
long	get_miliseconds(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (print_error(ERR_TIME));
	return ((long)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

int	get_actual_time(t_philo *philo)
{
	return (get_miliseconds() - philo->start_time);
}

void	smol_sleep(int wait_time)
{
	long	end;

	end = get_miliseconds() + wait_time;
	while (get_miliseconds() < end)
	{
		usleep(100);
	}
}

/* No need for mutex because applies before routine starts */
int	set_start_time(t_waiter *waiter)
{
	int	i;

	waiter->start_time = get_miliseconds();
	if (waiter->start_time == 0)
		return (ERR_TIME);
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
