/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 21:37:38 by alex              #+#    #+#             */
/*   Updated: 2025/01/11 18:58:32 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static void	lonely_dinner(t_philo *philo)
// {
// 	return ;
// }


static void	think(t_philo *philo)
{
	write_status(THINKING, philo, 1);
}

/* Locks first fork, report, locks second fork, report,
set last meal time, report eating, sleep for eating time,
set sated if max meal reached, unlocks forks */
static void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork->fork);
	write_status(TAKE_FIRST_FORK, philo, 1);
	pthread_mutex_lock(philo->second_fork->fork);
	write_status(TAKE_SECOND_FORK, philo, 1);
	setter(&philo->philo_mutex, &philo->last_meal_time, get_miliseconds());
	philo->meal_count++;
	write_status(EATING, philo, 1);
	micro_usleep(philo->waiter->time_to_die, philo->waiter);
	if (philo->waiter->max_meals > 0
		&& philo->meal_count == philo->waiter->max_meals)
		setter(&philo->philo_mutex, &philo->is_sated, true);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

/* Once all philosopher are seated, */
void	*dine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_on_philosophers(philo->waiter);
	while (!dinner_has_ended(philo->waiter))
	{
		if (philo->is_sated == true)
			break ;
		eat(philo);
		write_status(SLEEPING, philo, true);
		micro_usleep(philo->waiter->time_to_sleep, philo->waiter);
		think(philo);
	}
	return (NULL);
}

int	start_dinner(t_waiter *waiter)
{
	int	i;

	printf("Dinner about to start\n");
	if (waiter->max_meals == 0)
		return (1);
	if (waiter->philo_total == 1)
		return (1); // TO DO
	i = 0;
	while (i < waiter->philo_total)
	{
		if (pthread_create(&waiter->philo_array[i]->thread, NULL, dine, waiter->philo_array[i]) != 0)
			return (print_error(ERR_THREAD));
		printf("Thread %d launched\n", i);
		i++;
	}
	printf("Getting time\n");
	waiter->start_time = get_miliseconds();
	if (waiter->start_time == 0)
		return (1);
	printf("Dinner Start = %d\n", waiter->start_time);
	setter(&waiter->table_mutex, &waiter->is_ready, true);
	printf("Ready to start\n");
	i = 0;
	while (i < waiter->philo_total)
	{
		printf("Joining philosopher %d\n", i);
		if (pthread_join(waiter->philo_array[i]->thread, NULL) != 0)
			return (print_error(ERR_THREAD));
		printf("Philosopher %d joined\n", i);
		i++;
	}
	return (0);
}