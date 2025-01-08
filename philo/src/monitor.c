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

int	create_philo(t_waiter *waiter)
{
	int			i;

	waiter->philo_array = malloc(sizeof(t_philo) * waiter->philo_count - 1);
	i = 0;
	while (i < waiter->philo_count)
	{
		waiter->philo_array[i]->id = i;
		waiter->philo_array[i]->last_meal = -1;
		waiter->philo_array[i]->retval = ft_calloc(sizeof(int), 1);
		pthread_create(&waiter->philo_array[i]->thread, NULL, &routine, (void *)(&waiter->philo_array[i]));
		// "Failed to thread", NULL);
		printf("Created thread %d\n", i);
		i++;
	}
	i = 0;
	while (i < waiter->philo_count - 1)
	{
		pthread_mutex_init(&waiter->philo_array[i]->fork, NULL);
		printf("Created fork %d\n", i);
	}
}


