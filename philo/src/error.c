/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:15:01 by mkling            #+#    #+#             */
/*   Updated: 2025/01/11 18:50:48 by mkling           ###   ########.fr       */
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

int	print_if_error(int action, int status)
{
	if (status == 0)
		return (0);
	if (status == EINVAL && action != INIT && action != CREATE)
		ft_putstr_fd("The value specified by mutex is invalid.", 2);
	else if (status == EINVAL && (action == INIT || action == CREATE))
		ft_putstr_fd("The value specified by attr is invalid.", 2);
	else if (status == EDEADLK)
		ft_putstr_fd("Deadlock detected.", 2);
	else if (status == ENOMEM)
		ft_putstr_fd("No memory to create another mutex.", 2);
	else if (status == EBUSY)
		ft_putstr_fd("Mutex is locked.", 2);
	else if (status == ESRCH)
		ft_putstr_fd("No corresponding thread found.", 2);
	else if (status == EPERM)
		ft_putstr_fd("Permission denied.", 2);
	else if (status == EAGAIN)
		ft_putstr_fd("No ressource to create another thread.", 2);
	return (status);
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
