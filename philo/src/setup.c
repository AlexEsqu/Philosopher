/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:58:54 by alex              #+#    #+#             */
/*   Updated: 2025/01/14 10:22:20 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	setter(pthread_mutex_t *mutex, int *destination, int value)
{
	printf("SETTER: lock mutex %p\n", mutex);
	if (pthread_mutex_lock(mutex) != 0)
		return (1);
	*destination = value;
	if (pthread_mutex_unlock(mutex) != 0)
		return (1);
	printf("SETTER: unlock mutex %p\n", mutex);
	return (0);
}

int	getter(pthread_mutex_t *mutex, int *value)
{
	int	result;

	printf("GETTER: lock mutex %p\n", mutex);
	if (!mutex || !value)
		return (print_error(ERR_MUTEX));
	if (pthread_mutex_lock(mutex) != 0)
		return (print_error(ERR_MUTEX));
	result = *value;
	if (pthread_mutex_unlock(mutex) != 0)
		return (print_error(ERR_MUTEX));
	printf("GETTER: unlock mutex %p\n", mutex);
	return (result);
}

static int	assign_forks(t_philo *philo, int seat)
{
	if (pthread_mutex_init(&philo->left_fork, NULL) != 0)
		return (print_error(ERR_MUTEX));
	philo->right_fork = &philo->waiter->philo_array[seat + 1]->left_fork;
	return (0);
}

static int	seat_philosophers(t_waiter *waiter)
{
	int			seat;
	t_philo		*philo;

	seat = 0;
	waiter->philo_array = malloc(sizeof(t_philo) * waiter->philo_total);
	while (seat < waiter->philo_total)
	{
		philo = malloc(sizeof(t_philo));
		philo->id = seat + 1;
		philo->is_sated = false;
		philo->meal_count = 0;
		philo->waiter = waiter;
		waiter->philo_array[seat] = philo;
		if (pthread_mutex_init(&philo->philo_mutex, NULL) != 0)
			return (print_error(ERR_MUTEX));
		if (assign_forks(philo, seat) != 0)
			return (ERR_MUTEX);
		seat++;
	}
	return (0);
}

int	set_table(t_waiter *waiter)
{
	waiter->is_dinner_ongoing = false;
	waiter->is_ready = false;
	if (pthread_mutex_init(&waiter->waiter_mutex, NULL) != 0)
		return (print_error(ERR_MUTEX));
	if (pthread_mutex_init(&waiter->write_mutex, NULL) != 0)
		return (print_error(ERR_MUTEX));
	if (seat_philosophers(waiter) != 0)
		return (1);
	return (0);
}
