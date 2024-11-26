/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:20:53 by mkling            #+#    #+#             */
/*   Updated: 2024/11/26 16:47:55 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo)
{
	usleep(200);
	pthread_mutex_lock(&((t_philo *)philo)->fork);
	printf("I am philosopher %d\n", ((t_philo *)philo)->id);
	printf("Philosopher %d started using fork\n", ((t_philo *)philo)->id);
	usleep(100);
	printf("Philosopher %d stopped using fork\n", ((t_philo *)philo)->id);
	usleep(100);
	pthread_mutex_unlock(&((t_philo *)philo)->fork);
	return (NULL);
}

void	create_philo(t_monitor *monitor)
{
	int			i;

	monitor->philo = malloc(sizeof(t_philo) * monitor->philo_count - 1);
	i = 0;
	while (i < monitor->philo_count)
	{
		monitor->philo[i].id = i;
		monitor->philo[i].last_meal = -1;
		exit_if(pthread_create(&monitor->philo[i].thread, NULL, &routine,
				(void *)(&monitor->philo[i])),
			"Failed to create a thread", NULL);
		printf("Created thread %d\n", i);
		if (i > 0)
		{
			pthread_mutex_init(&monitor->philo[i].fork, NULL);
			printf("Created fork %d\n", i);
		}
		i++;
	}
}

void	init_monitor(int argc, char **argv, t_monitor *monitor)
{
	monitor->philo_count = ft_atoi(argv[NUMBER_OF_PHILOSOPHER]);
	monitor->time_to_die = ft_atoi(argv[TIME_TO_DIE]);
	monitor->time_to_eat = ft_atoi(argv[TIME_TO_EAT]);
	monitor->time_to_sleep = ft_atoi(argv[TIME_TO_SLEEP]);
	if (argc == 6)
		monitor->meal_count = ft_atoi(argv[NUMBER_OF_MEALS]);
	else
		monitor->meal_count = -1;
}
