/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:37:59 by mkling            #+#    #+#             */
/*   Updated: 2024/11/26 16:42:59 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_forks(t_monitor *monitor)
{
	int	i;

	i = 1;
	while (i < monitor->philo_count)
	{
		pthread_mutex_destroy(&monitor->philo[i].fork);
		printf("Destroyed fork %d\n", i);
		i++;
	}
}

void	clean_up(t_monitor *monitor)
{
	destroy_forks(monitor);
	free(monitor->philo);
}
