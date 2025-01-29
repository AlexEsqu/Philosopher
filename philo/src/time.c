/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:36:42 by mkling            #+#    #+#             */
/*   Updated: 2025/01/29 09:00:30 by alex             ###   ########.fr       */
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

/* No need for mutex because all threads will only read waiter's start time
once set up by set start time */
int	get_actual_time(t_philo *philo)
{
	long	time;

	time = get_miliseconds() - philo->waiter->start_time;
	return (time);
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
	waiter->start_time = get_miliseconds();
	if (waiter->start_time == 0)
		return (ERR_TIME);
	return (SUCCESS);
}

void	wait_until_philo_are_seated(t_waiter *waiter)
{
	while (getter(&waiter->waiter_mutex, &waiter->is_on) == false)
		usleep(10);
}
