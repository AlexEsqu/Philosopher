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

	if (gettimeofday(&time, NULL) == -1)
	{
		printf("Failed to get the time through gettimeofday");
		free(monitor);
		return (0);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep()
{
	return ;
}

void	wait_on_philo(t_monitor *monitor)
{
	int	i;
	int	retval;

	i = 0;
	while (i <= monitor->philo_count - 1)
	{
		pthread_join(monitor->philo_array[i]->thread, monitor->philo_array[i]->retval)
		if (monitor->philo_array[i].retval != 0)
			return (printf("Failed to join thread"));
		i++;
	}
}
