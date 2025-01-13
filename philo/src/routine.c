/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 21:37:38 by alex              #+#    #+#             */
/*   Updated: 2025/01/14 00:22:16 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	lonely_dinner(t_philo *philo)
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
report eating, sleep for eating time, set sated if max meal reached, unlocks forks */
static void	eat(t_philo *philo,
	pthread_mutex_t *first_fork, pthread_mutex_t *second_fork)
{
	pthread_mutex_lock(first_fork);
	write_status(TAKE_FIRST_FORK, philo, 1);
	pthread_mutex_lock(second_fork);
	write_status(TAKE_SECOND_FORK, philo, 1);
	setter(&philo->philo_mutex, &philo->last_meal_time, get_actual_time());
	philo->meal_count++;
	write_status(EATING, philo, 1);
	micro_usleep(philo->waiter->time_to_die, philo->waiter);
	if (philo->waiter->max_meals > 0
		&& philo->meal_count == philo->waiter->max_meals)
		setter(&philo->philo_mutex, &philo->is_sated, true);
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
}

/* Once all philosopher are seated, */
void	*dine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_until_philo_are_seated(philo->waiter);
	printf("Dinner has started\n");
	while (!dinner_has_ended(philo->waiter))
	{
		if (philo->is_sated)
			break ;
		if (philo->id % 2)
			eat(philo, &philo->left_fork, philo->right_fork);
		if (philo->id % 2)
			eat(philo, philo->right_fork, &philo->left_fork);
		write_status(SLEEPING, philo, true);
		micro_usleep(philo->waiter->time_to_sleep, philo->waiter);
		think(philo);
	}
	return (NULL);
}

int	start_dinner(t_waiter *waiter)
{
	int	i;

	if (waiter->max_meals == 0)
		return (1);
	if (waiter->philo_total == 1)
		return (lonely_dinner(waiter->philo_array[0]));
	i = 0;
	while (i < waiter->philo_total)
	{
		if (pthread_create(&waiter->philo_array[i]->thread,
				NULL, dine, waiter->philo_array[i]) != 0)
			return (print_error(ERR_THREAD));
		i++;
	}
	waiter->start_time = get_miliseconds();
	if (waiter->start_time == 0)
		return (1);
	setter(&waiter->waiter_mutex, &waiter->is_ready, true);
	printf("Ready to start\n");
	i = 0;
	while (i < waiter->philo_total)
	{
		if (pthread_join(waiter->philo_array[i]->thread, NULL) != 0)
			return (print_error(ERR_THREAD));
		i++;
	}
	return (0);
}
