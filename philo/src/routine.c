/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 21:37:38 by alex              #+#    #+#             */
/*   Updated: 2025/01/15 12:01:11 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lonely_dinner(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	write_status(TAKE_FIRST_FORK, philo, 1);
	micro_usleep(philo->waiter->time_to_die, philo->waiter);
	write_status(DIED, philo, 1);
	pthread_mutex_unlock(&philo->left_fork);
	return (0);
}

static void	think(t_philo *philo)
{
	write_status(THINKING, philo, 1);
}

/* Locks first fork, report, locks second fork, report, set last meal time,
report eating, sleep for eating time, set sated if max meal, unlocks forks */
static void	eat(t_philo *philo,
	pthread_mutex_t *first_fork, pthread_mutex_t *second_fork)
{
	pthread_mutex_lock(first_fork);
	write_status(TAKE_FIRST_FORK, philo, 1);
	pthread_mutex_lock(second_fork);
	write_status(TAKE_SECOND_FORK, philo, 1);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_meal_time = get_actual_time();
	philo->meal_count++;
	if (philo->meal_count == philo->waiter->max_meals)
		philo->is_sated = true;
	pthread_mutex_unlock(&philo->philo_mutex);
	write_status(EATING, philo, 1);
	micro_usleep(philo->waiter->time_to_eat, philo->waiter);
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
}

/* Once all philosopher are seated, */
void	*dine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_until_philo_are_seated(philo->waiter);
	while (!dinner_has_ended(philo->waiter))
	{
		if (philo->is_sated)
			break ;
		if (philo->id % 2 == 0)
			eat(philo, &philo->left_fork, philo->right_fork);
		if (philo->id % 2 != 0)
			eat(philo, philo->right_fork, &philo->left_fork);
		write_status(SLEEPING, philo, true);
		micro_usleep(philo->waiter->time_to_sleep, philo->waiter);
		think(philo);
	}
	return (NULL);
}
