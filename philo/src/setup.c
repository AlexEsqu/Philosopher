/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:58:54 by alex              #+#    #+#             */
/*   Updated: 2025/01/16 14:00:05 by mkling           ###   ########.fr       */
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

static int	assign_right_forks(t_waiter *waiter)
{
	int		seat;
	int		philo_total;
	t_philo	*philo;
	t_philo	*right_neighbor;

	seat = 0;
	philo_total = waiter->philo_total;
	while (seat < philo_total)
	{
		philo = waiter->philo_array[seat];
		right_neighbor = philo->waiter->philo_array[(seat + 1) % philo_total];
		philo->right_fork = &right_neighbor->left_fork;
		seat++;
	}
	return (0);
}

static int	seat_philosophers(t_waiter *waiter)
{
	int			seat;
	t_philo		*philo;

	seat = 0;
	waiter->philo_array = ft_calloc(waiter->philo_total, sizeof(t_philo *));
	while (seat < waiter->philo_total)
	{
		philo = ft_calloc(1, sizeof(t_philo));
		philo->id = seat + 1;
		philo->is_sated = false;
		philo->start_time = -1;
		philo->meal_count = 0;
		philo->time_to_die = waiter->time_to_die;
		philo->time_to_eat = waiter->time_to_eat;
		philo->time_to_sleep = waiter->time_to_sleep;
		philo->max_meals = waiter->max_meals;
		philo->waiter = waiter;
		waiter->philo_array[seat] = philo;
		if (pthread_mutex_init(&philo->philo_mutex, NULL) != 0)
			return (print_error(ERR_MUTEX));
		if (pthread_mutex_init(&philo->left_fork, NULL) != 0)
			return (print_error(ERR_MUTEX));
		seat++;
	}
	return (0);
}

int	set_table(t_waiter *waiter)
{
	waiter->is_on = false;
	if (pthread_mutex_init(&waiter->waiter_mutex, NULL) != 0)
		return (print_error(ERR_MUTEX));
	if (pthread_mutex_init(&waiter->write_mutex, NULL) != 0)
		return (print_error(ERR_MUTEX));
	if (seat_philosophers(waiter) != 0)
		return (1);
	if (assign_right_forks(waiter) != 0)
		return (ERR_MUTEX);
	return (0);
}
