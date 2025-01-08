/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:18:14 by alex              #+#    #+#             */
/*   Updated: 2025/01/08 20:39:02 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int print_if_error(int action, int status)
{
    if (status == 0)
        return (0);
    if (status == EINVAL && action != INIT)
        printf("The value specified by mutex is invalid.");
    else if (status == EINVAL && action == INIT)
        printf("The value specified by attr is invalid.");
    else if (status == EDEADLK)
        printf("Deadlock would occur if the thread blocked waiting for mutex.");
    else if (status == ENOMEM)
        printf("The process cannot get enough memory to create another mutex.");
    else if (status == EBUSY)
        printf("Mutex is locked.");
    return (1);
}

int    mutex_do(int action, t_mutex *mutex)
{
    if (action == INIT)
        return (print_if_error(action, pthread_mutex_init(mutex, NULL)));
    else if (action == LOCK)
        return (print_if_error(action, pthread_mutex_lock(mutex)));
    else if (action == UNLOCK)
        return (print_if_error(action, pthread_mutex_unlock(mutex)));
    else if (action == DESTROY)
        return (print_if_error(action, pthread_mutex_destroy(mutex)));
}
