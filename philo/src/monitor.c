/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 23:16:48 by alex              #+#    #+#             */
/*   Updated: 2025/01/13 11:19:32 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	write_status_debug(int status, t_philo *philo)
{
	printf("%ld %d ", get_actual_time(), philo->id);
	if (status == TAKE_FIRST_FORK && !dinner_has_ended(philo->waiter))
		printf("has taken a fork\n");
	if (status == TAKE_SECOND_FORK && !dinner_has_ended(philo->waiter))
		printf("has taken the second fork\n");
	else if (status == EATING && !dinner_has_ended(philo->waiter))
		printf("is eating their %d th meal\n", philo->meal_count);
	else if (status == SLEEPING && !dinner_has_ended(philo->waiter))
		printf("is sleeping\n");
	else if (status == THINKING && !dinner_has_ended(philo->waiter))
		printf("is thinking\n");
	else if (status == DIED)
		printf("died\n");
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
		printf("%ld %d ", get_actual_time(), philo->id);
		if (status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
			printf("has taken a fork\n");
		else if (status == EATING)
			printf("is eating\n");
		else if (status == SLEEPING)
			printf("is sleeping\n");
		else if (status == THINKING)
			printf("is thinking\n");
		else if (status == DIED)
			printf("died\n");
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
	return (last_meal_time > philo->waiter->time_to_die);
}

int	starvation(t_waiter *waiter)
{
	int	i;

	while (!dinner_has_ended(waiter))
	{
		i = 0;
		while (!dinner_has_ended(waiter) && i < waiter->philo_total)
		{
			if (is_starving(&waiter->philo_array[i]))
				setter(&waiter->table_mutex, &waiter->is_end, true);
		}
		micro_usleep(10, waiter);
	}
	return (0);
}
