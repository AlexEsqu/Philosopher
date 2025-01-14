/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:15:01 by mkling            #+#    #+#             */
/*   Updated: 2025/01/14 10:49:18 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	print_error(int error_code)
{
	if (error_code == ERR_MALLOC)
		ft_putstr_fd("Failed to allocate memory.", 2);
	if (error_code == ERR_MUTEX)
		ft_putstr_fd("Mutex failed\n", 2);
	if (error_code == ERR_THREAD)
		ft_putstr_fd("Thread failed\n", 2);
	if (error_code == ERR_TIME)
		ft_putstr_fd("Faile to get the time through gettimeofday", 2);
	else
		ft_putstr_fd("Error", 2);
	return (error_code);
}

void	free_waiter(t_waiter *waiter)
{
	int	i;

	if (!waiter)
		return ;
	if (waiter->philo_array != NULL)
	{
		i = 0;
		while (i < waiter->philo_total)
		{
			if (waiter->philo_array[i] != NULL)
			{
				pthread_mutex_destroy(&waiter->philo_array[i]->left_fork);
				free(waiter->philo_array[i]);
			}
			i++;
		}
		free(waiter->philo_array);
	}
	free(waiter);
}
