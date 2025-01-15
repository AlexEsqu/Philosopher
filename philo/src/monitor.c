/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 23:16:48 by alex              #+#    #+#             */
/*   Updated: 2025/01/15 14:27:14 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	write_status_debug(int status, t_philo *philo)
{
	if (status == TAKE_FIRST_FORK && !dinner_has_ended(philo->waiter))
		printf("%ld %d has taken a fork\n", get_actual_time(), philo->id);
	if (status == TAKE_SECOND_FORK && !dinner_has_ended(philo->waiter))
		printf("%ld %d has taken a second fork\n", get_actual_time(), philo->id);
	else if (status == EATING && !dinner_has_ended(philo->waiter))
		printf("%ld %d is eating their %d th meal\n", get_actual_time(), philo->id, philo->meal_count);
	else if (status == SLEEPING && !dinner_has_ended(philo->waiter))
		printf("%ld %d is sleeping\n", get_actual_time(), philo->id);
	else if (status == THINKING && !dinner_has_ended(philo->waiter))
		printf("%ld %d is thinking\n", get_actual_time(), philo->id);
	else if (status == DIED)
		printf("%ld %d died\n", get_actual_time(), philo->id);
	return (0);
}

int	write_status(int status, t_philo *philo, bool debug)
{
	if (pthread_mutex_lock(&philo->waiter->write_mutex) != 0)
		return (1);
	if (debug)
		write_status_debug(status, philo);
	else if (!dinner_has_ended(philo->waiter))
	{
		if (status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
			printf("%ld %d has taken a fork\n", get_actual_time(), philo->id);
		else if (status == EATING)
			printf("%ld %d is eating\n", get_actual_time(), philo->id);
		else if (status == SLEEPING)
			printf("%ld %d is sleeping\n", get_actual_time(), philo->id);
		else if (status == THINKING)
			printf("%ld %d is thinking\n", get_actual_time(), philo->id);
		else if (status == DIED)
			printf("%ld %d died\n", get_actual_time(), philo->id);
	}
	if (pthread_mutex_unlock(&philo->waiter->write_mutex) != 0)
		return (1);
	return (0);
}

int	is_starving(t_philo *philo)
{
	long	last_meal_time;
	long	since_last_meal;

	last_meal_time = getter(&philo->philo_mutex, &philo->last_meal_time);
	since_last_meal = get_actual_time() - last_meal_time;
	return (since_last_meal > philo->waiter->time_to_die);
}

int	check_if_starving_or_sated(t_waiter *waiter)
{
	int	i;
	int	sated_count;

	while (!dinner_has_ended(waiter))
	{
		i = 0;
		sated_count = 0;
		while (!dinner_has_ended(waiter) && i < waiter->philo_total)
		{
			if (is_starving(waiter->philo_array[i]))
			{
				setter(&waiter->waiter_mutex,
					&waiter->is_dinner_ongoing, false);
				write_status(DIED, waiter->philo_array[i], true);
			}
			if (getter(&waiter->philo_array[i]->philo_mutex,
					&waiter->philo_array[i]->is_sated))
				sated_count++;
			if (sated_count == waiter->philo_total)
				setter(&waiter->waiter_mutex, &waiter->is_dinner_ongoing, false);
		}
		micro_usleep(10, waiter);
	}
	return (0);
}
