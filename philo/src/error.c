/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:15:01 by mkling            #+#    #+#             */
/*   Updated: 2025/01/13 11:18:44 by mkling           ###   ########.fr       */
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
	else
		ft_putstr_fd("Error", 2);
	return (error_code);
}

void	clean_up(t_waiter *waiter)
{
	pthread_mutex_destroy(&waiter->table_mutex);
	pthread_mutex_destroy(&waiter->write_mutex);
}
