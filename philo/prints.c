/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:36:11 by mkling            #+#    #+#             */
/*   Updated: 2024/10/30 19:55:31 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	struct timeval	time;

	printf("%d %d is eating\n", philo->id, gettimeofday(&time, NULL));
}

void	take(t_philo *philo)
{
	struct timeval	time;

	printf("%d %d has taken a fork\n", philo->id, gettimeofday(&time, NULL));
}

void	sleep(t_philo *philo)
{
	struct timeval	time;

	printf("%d %d is sleeping\n", philo->id, gettimeofday(&time, NULL));
}

void	think(t_philo *philo)
{
	struct timeval	time;

	printf("%d %d is thinking\n", philo->id, gettimeofday(&time, NULL));
}

void	die(t_philo *philo)
{
	struct timeval	time;

	printf("%d %d died\n", philo->id, gettimeofday(&time, NULL));
}
