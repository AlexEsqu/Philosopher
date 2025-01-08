/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:58:54 by alex              #+#    #+#             */
/*   Updated: 2025/01/09 00:03:58 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	setter(t_mutex *mutex, int *destination, int value)
{
	if (mutex_do(LOCK, mutex) != 0)
		return (1);
	*destination = value;
	if (mutex_do(UNLOCK, mutex) != 0)
		return (1);
	return (0);
}

int	getter(t_mutex *mutex, int *value)
{
	int	result;

	if (mutex_do(LOCK, mutex) != 0)
		return (-1);
	result = *value;
	if (mutex_do(UNLOCK, mutex) != 0)
		return (-1);
	return (result);
}

static void	assign_forks(t_philo *philo, t_fork **fork_array, int seat_number)
{
	int	philo_total;

	philo_total = philo->waiter->philo_total;
	philo->first_fork = fork_array[(seat_number + 1) % philo_total];
	philo->second_fork = fork_array[seat_number];
	if (philo->id % 2)
	{
		philo->first_fork = fork_array[seat_number];
		philo->second_fork = fork_array[(seat_number + 1) % philo_total];
	}
}

static int	invite_philosopher(t_waiter *waiter)
{
	int			seat;
	t_philo		*philo;

	seat = 0;
	while (seat < waiter->philo_total)
	{
		philo = waiter->philo_array[seat];
		philo->id = seat + 1;
		philo->is_sated = false;
		philo->meal_count = 0;
		philo->waiter = waiter;
		if (mutex_do(INIT, &philo->philo_mutex) != 0)
			return (1);
		assign_forks(philo, waiter->fork_array, seat);
		seat++;
	}
	return (0);
}

int	set_table(t_waiter *waiter)
{
	int	i;

	waiter->is_end = false;
	waiter->is_end = false;
	if (mutex_do(INIT, &waiter->table_mutex) != 0)
		return (1);
	waiter->philo_array = malloc(sizeof(t_philo) * waiter->philo_total);
	if (!waiter->philo_array)
		return (1);
	waiter->fork_array = malloc(sizeof(t_fork) * waiter->philo_total);
	if (waiter->fork_array)
		return (1);
	i = 0;
	while (i < waiter->philo_total)
	{
		if (mutex_do(INIT, &waiter->fork_array[i]->fork) != 0)
			return (1);
		waiter->fork_array[i]->fork_id = i;
		i++;
	}
	invite_philosopher(waiter);
	return (0);
}
