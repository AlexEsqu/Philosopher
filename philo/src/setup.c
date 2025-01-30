/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:58:54 by alex              #+#    #+#             */
/*   Updated: 2025/01/30 12:27:52 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	setter(pthread_mutex_t *mutex, int *destination, int value)
{
	if (pthread_mutex_lock(mutex) != 0)
		return (print_error(ERR_MUTEX));
	*destination = value;
	if (pthread_mutex_unlock(mutex) != 0)
		return (print_error(ERR_MUTEX));
	return (SUCCESS);
}

int	getter(pthread_mutex_t *mutex, int *value)
{
	int	result;

	if (pthread_mutex_lock(mutex) != 0)
		return (print_error(ERR_MUTEX));
	result = *value;
	if (pthread_mutex_unlock(mutex) != 0)
		return (print_error(ERR_MUTEX));
	return (result);
}

static void	assign_forks(t_waiter *waiter)
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
}

static int	seat_philosophers(t_waiter *waiter)
{
	int			seat;
	t_philo		*philo;

	seat = 0;
	waiter->philo_array = ft_calloc(waiter->philo_total, sizeof(t_philo *));
	if (!waiter->philo_array)
		return (ERR_GENERAL);
	while (seat < waiter->philo_total)
	{
		philo = ft_calloc(1, sizeof(t_philo));
		if (!philo)
			return (print_error(ERR_MALLOC));
		philo->id = seat + 1;
		philo->is_sated = false;
		philo->last_meal_time = -1;
		philo->meal_count = 0;
		philo->waiter = waiter;
		waiter->philo_array[seat] = philo;
		if (pthread_mutex_init(&philo->philo_mutex, NULL) != 0)
			return (print_error(ERR_MUTEX));
		if (pthread_mutex_init(&philo->left_fork, NULL) != 0)
			return (print_error(ERR_MUTEX));
		seat++;
	}
	return (SUCCESS);
}

int	set_table(t_waiter *waiter)
{
	waiter->is_on = false;
	if (pthread_mutex_init(&waiter->waiter_mutex, NULL) != 0)
		return (print_error(ERR_MUTEX));
	if (pthread_mutex_init(&waiter->write_mutex, NULL) != 0)
		return (print_error(ERR_MUTEX));
	if (seat_philosophers(waiter) != 0)
		return (ERR_GENERAL);
	assign_forks(waiter);
	return (SUCCESS);
}
