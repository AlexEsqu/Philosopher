/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 21:37:38 by alex              #+#    #+#             */
/*   Updated: 2025/01/20 10:11:42 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lonely_dinner(t_philo *philo)
{
	philo->start_time = get_miliseconds();
	pthread_mutex_lock(&philo->left_fork);
	printf("%d %d has taken a fork\n", get_actual_time(philo), philo->id);
	smol_sleep(philo->waiter->time_to_die);
	printf("%d %d died\n", get_actual_time(philo), philo->id);
	pthread_mutex_unlock(&philo->left_fork);
	return (SUCCESS);
}

static void	think(t_philo *philo)
{
	long	time_to_think;

	pthread_mutex_lock(&philo->philo_mutex);
	time_to_think = (philo->waiter->time_to_die - (get_actual_time(philo)
				- philo->last_meal_time) - philo->waiter->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->philo_mutex);
	write_status(THINKING, philo);
	smol_sleep(time_to_think);
}

/* Locks first fork, report, locks second fork, report, set last meal time,
report eating, sleep for eating time, set sated if max meal, unlocks forks */
static void	eat(t_philo *philo,
		pthread_mutex_t *first_fork, pthread_mutex_t *second_fork)
{
	pthread_mutex_lock(first_fork);
	write_status(TAKE_FIRST_FORK, philo);
	pthread_mutex_lock(second_fork);
	write_status(TAKE_SECOND_FORK, philo);
	write_status(EATING, philo);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_meal_time = get_actual_time(philo);
	philo->meal_count++;
	if (philo->meal_count == philo->waiter->max_meals)
		philo->is_sated = true;
	pthread_mutex_unlock(&philo->philo_mutex);
	smol_sleep(philo->waiter->time_to_eat);
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
	write_status(SLEEPING, philo);
	smol_sleep(philo->waiter->time_to_sleep);
	think(philo);
}

/* Once all philosopher are seated, */
void	*dine(void *data)
{
	t_philo	*philo;
	int		meal_count;

	philo = (t_philo *)data;
	meal_count = 0;
	wait_until_philo_are_seated(philo->waiter);
	if (philo->id % 2)
	{
		write_status(THINKING, philo);
		smol_sleep(philo->waiter->time_to_eat);
	}
	while (!dinner_has_ended(philo->waiter))
	{
		if (philo->id % 2 == 0)
			eat(philo, &philo->left_fork, philo->right_fork);
		else
			eat(philo, philo->right_fork, &philo->left_fork);
		meal_count++;
		if (meal_count == philo->waiter->max_meals)
			break ;
	}
	return (NULL);
}
