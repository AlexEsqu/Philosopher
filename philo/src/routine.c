/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 21:37:38 by alex              #+#    #+#             */
/*   Updated: 2025/01/16 10:06:30 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lonely_dinner(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	printf("%ld %d has taken a fork\n", get_actual_time(philo), philo->id);
	micro_usleep(philo->time_to_die, philo->waiter);
	write_status(DIED, philo, 1);
	pthread_mutex_unlock(&philo->left_fork);
	return (0);
}

static void	think(t_philo *philo)
{
	long	time_to_think;

	pthread_mutex_lock(&philo->philo_mutex);
	time_to_think = (philo->time_to_die - (get_actual_time(philo)
				- philo->last_meal_time) - philo->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->philo_mutex);
	if (time_to_think < 0)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	write_status(THINKING, philo, 1);
	micro_usleep((size_t)time_to_think, philo->waiter);
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
	write_status(EATING, philo, 1);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_meal_time = get_actual_time(philo);
	philo->meal_count++;
	if (philo->meal_count == philo->max_meals)
		philo->is_sated = true;
	pthread_mutex_unlock(&philo->philo_mutex);
	micro_usleep(philo->time_to_eat, philo->waiter);
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
	write_status(SLEEPING, philo, 1);
	micro_usleep(philo->time_to_sleep, philo->waiter);
}

/* Once all philosopher are seated, */
void	*dine(void *data)
{
	t_philo	*philo;
	int		meal_count;

	philo = (t_philo *)data;
	meal_count = 0;
	wait_until_philo_are_seated(philo->waiter);
	while (!dinner_has_ended(philo->waiter))
	{
		if (philo->id % 2 == 0)
			eat(philo, &philo->left_fork, philo->right_fork);
		else
			eat(philo, philo->right_fork, &philo->left_fork);
		meal_count++;
		write_status(SLEEPING, philo, true);
		micro_usleep(philo->time_to_sleep, philo->waiter);
		think(philo);
	}
	return (NULL);
}
