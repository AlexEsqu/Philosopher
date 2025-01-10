/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:58:54 by alex              #+#    #+#             */
/*   Updated: 2025/01/10 17:31:51 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	setter(pthread_mutex_t *mutex, int *destination, int value)
{
	if (pthread_mutex_lock(mutex) != 0)
		return (1);
	*destination = value;
	if (pthread_mutex_unlock(mutex) != 0)
		return (1);
	return (0);
}

int	getter(pthread_mutex_t *mutex, int *value)
{
	int	result;

	if (pthread_mutex_lock(mutex) != 0)
		return (-1);
	result = *value;
	if (pthread_mutex_unlock(mutex) != 0)
		return (-1);
	return (result);
}

static int	init_forks(t_waiter *waiter)
{
	int	i;

	waiter->fork_array = malloc(sizeof(t_fork) * waiter->philo_total);
	if (!waiter->fork_array)
		return (print_error(ERR_MALLOC));
	i = 0;
	while (i < waiter->philo_total)
	{
		waiter->fork_array[i] = malloc(sizeof(t_fork));
		if (pthread_mutex_init(&waiter->fork_array[i]->fork, 0) != 0)
			return (print_error(ERR_MUTEX));
		waiter->fork_array[i]->fork_id = i;
		i++;
	}
	return (SUCCESS);
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

static int	init_philosophers(t_waiter *waiter)
{
	int			seat;
	t_philo		*philo;

	printf("- inviting philosophers\n");
	waiter->philo_array = malloc(sizeof(t_philo) * waiter->philo_total);
	if (!waiter->philo_array)
		return (1);
	seat = 0;
	printf("- seating philosophers\n");
	while (seat < waiter->philo_total)
	{
		waiter->philo_array[seat] = malloc(sizeof(t_philo));
		philo = waiter->philo_array[seat];
		if (!philo)
			return (print_error(ERR_MALLOC));
		philo->id = seat + 1;
		philo->is_sated = false;
		philo->meal_count = 0;
		philo->waiter = waiter;
		philo->philo_mutex = malloc(sizeof(pthread_mutex_t));
		if (pthread_mutex_init(philo->philo_mutex, 0) != 0)
			return (print_error(ERR_MUTEX));
		assign_forks(philo, waiter->fork_array, seat);
		seat++;
	}
	return (0);
}

int	set_table(t_waiter *waiter)
{
	printf("Setting table\n");
	waiter->is_end = false;
	waiter->is_ready = false;
	waiter->table_mutex = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(waiter->table_mutex, 0) != 0)
		return (print_error(ERR_MUTEX));
	printf("Setting forks\n");
	if (init_forks(waiter) != 0)
		return (1);
	printf("Seating philosophers\n");
	if (init_philosophers(waiter) != 0)
		return (1);
	return (0);
}
