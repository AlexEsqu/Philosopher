/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 23:16:48 by alex              #+#    #+#             */
/*   Updated: 2025/01/08 23:57:07 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	write_status_debug(int status, t_philo *philo, long elapsed)
{
	printf("%-6ld: %d ", elapsed, philo->id);
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
	long	elapsed;

	elapsed = get_miliseconds();
	if (mutex_do(LOCK, &philo->waiter->write_mutex) != 0)
		return (1);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else if (!dinner_has_ended(philo->waiter))
	{
		printf("%-6ld: %d ", elapsed, philo->id);
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
	if (mutex_do(UNLOCK, &philo->waiter->write_mutex) != 0)
		return (1);
	return (0);
}
