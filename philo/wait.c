/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:36:42 by mkling            #+#    #+#             */
/*   Updated: 2024/11/26 16:48:00 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_miliseconds(t_monitor *monitor)
{
	struct timeval	time;

	exit_if((gettimeofday(&time, NULL) == -1),
		"Failed to get the time through gettimeofday", monitor);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep()
{
	return ;
}

void	wait_on_philo(t_monitor *monitor)
{
	int	i;

	i = 0;
	while (i <= monitor->philo_count - 1)
	{
		exit_if(pthread_join(monitor->philo[i].thread, NULL),
			"Failed to join thread", NULL);
		i++;
	}
}
