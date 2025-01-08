/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:20:17 by mkling            #+#    #+#             */
/*   Updated: 2024/11/26 16:27:02 by mkling           ###   ########.fr       */
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

void	nap(t_philo *philo)
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
