/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:58:54 by alex              #+#    #+#             */
/*   Updated: 2025/01/11 18:47:37 by mkling           ###   ########.fr       */
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

	if (!mutex || !value)
		return (print_error(ERR_MUTEX));
	if (pthread_mutex_lock(mutex) != 0)
		return (print_error(ERR_MUTEX));
	result = *value;
	if (pthread_mutex_unlock(mutex) != 0)
		return (print_error(ERR_MUTEX));
	return (result);
}

static void	assign_forks(t_philo *philo, int seat)
{
	if (pthread_mutex_init(&philo->left_fork, NULL) != 0)
		return (print_error(ERR_MUTEX));
	philo->right_fork = &philo->waiter->philo_array[seat + 1].left_fork;
}

static int	seat_philosophers(t_waiter *waiter)
{
	int			seat;
	t_philo		philo;

	seat = 0;
	while (seat < waiter->philo_total)
	{
		philo = waiter->philo_array[seat];
		philo.id = seat + 1;
		philo.is_sated = false;
		philo.meal_count = 0;
		philo.waiter = waiter;
		if (pthread_mutex_init(&philo.philo_mutex, NULL) != 0)
			return (print_error(ERR_MUTEX));
		assign_forks(&philo, seat);
		seat++;
	}
	return (0);
}

int	set_table(t_waiter *waiter)
{
	waiter->is_end = false;
	waiter->is_ready = false;
	if (pthread_mutex_init(&waiter->table_mutex, NULL) != 0)
		return (print_error(ERR_MUTEX));
	if (pthread_mutex_init(&waiter->write_mutex, NULL) != 0)
		return (print_error(ERR_MUTEX));
	if (seat_all_philosophers(waiter) != 0)
		return (1);
	return (0);
}