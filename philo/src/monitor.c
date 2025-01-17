/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 23:16:48 by alex              #+#    #+#             */
/*   Updated: 2025/01/17 14:15:01 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	dinner_has_ended(t_waiter *waiter)
{
	return (getter(&waiter->waiter_mutex, &waiter->is_on) != true);
}

int	write_status(int status, t_philo *philo)
{
	if (pthread_mutex_lock(&philo->waiter->write_mutex) != 0)
		return (ERR_GENERAL);
	else if (!dinner_has_ended(philo->waiter))
	{
		if (status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
			printf("%d %d has taken a fork\n", get_actual_time(philo),
				philo->id);
		else if (status == EATING)
			printf("%d %d is eating\n", get_actual_time(philo), philo->id);
		else if (status == SLEEPING)
			printf("%d %d is sleeping\n", get_actual_time(philo), philo->id);
		else if (status == THINKING)
			printf("%d %d is thinking\n", get_actual_time(philo), philo->id);
		else if (status == DIED)
			printf("%d %d died\n", get_actual_time(philo), philo->id);
	}
	if (pthread_mutex_unlock(&philo->waiter->write_mutex) != 0)
		return (ERR_MUTEX);
	return (SUCCESS);
}

bool	starving_or_sated(t_philo *philo, int *sated_count)
{
	int		since_last_meal;
	bool	is_starved;
	bool	is_sated;

	if (pthread_mutex_lock(&philo->philo_mutex) != 0)
		return (print_error(ERR_MUTEX));
	{
		since_last_meal = (int)(get_actual_time(philo) - philo->last_meal_time);
		if (philo->is_sated)
			*sated_count = *sated_count + 1;
	}
	if (pthread_mutex_unlock(&philo->philo_mutex) != 0)
		return (print_error(ERR_MUTEX));
	is_starved = since_last_meal > philo->time_to_die;
	is_sated = *sated_count == philo->waiter->philo_total;
	if (is_starved || is_sated)
	{
		if (is_starved)
			write_status(DIED, philo);
		setter(&philo->waiter->waiter_mutex, &philo->waiter->is_on, false);
		return (true);
	}
	return (false);
}

int	check_if_starving_or_sated(t_waiter *waiter)
{
	int	i;
	int	sated_count;

	if (waiter->philo_total == 1)
		return (SUCCESS);
	while (!dinner_has_ended(waiter))
	{
		i = 0;
		sated_count = 0;
		while (i < waiter->philo_total)
		{
			if (starving_or_sated(waiter->philo_array[i++], &sated_count))
				return (SUCCESS);
		}
		usleep(1000);
	}
	return (ERR_GENERAL);
}
