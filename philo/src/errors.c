/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:18:14 by alex              #+#    #+#             */
/*   Updated: 2025/01/08 23:56:55 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int print_if_error(int action, int status)
{
    if (status == 0)
        return (0);
    if (action == MALLOC)
        printf("Failed to allocate memory.");
    if (status == EINVAL && action != INIT && action != CREATE)
        printf("The value specified by mutex is invalid.");
    else if (status == EINVAL && (action == INIT || action == CREATE))
        printf("The value specified by attr is invalid.");
    else if (status == EDEADLK)
        printf("Deadlock detected.");
    else if (status == ENOMEM)
        printf("No memory to create another mutex.");
    else if (status == EBUSY)
        printf("Mutex is locked.");
    else if (status == ESRCH)
        printf("No corresponding thread found.");
    else if (status == EPERM)
        printf("Permission denied.");
    else if (status == EAGAIN)
        printf("No ressource to create another thread.");
    return (1);
}

int mutex_do(int action, t_mutex *mutex)
{
    if (action == INIT)
        return (print_if_error(action, pthread_mutex_init(mutex, NULL)));
    else if (action == LOCK)
        return (print_if_error(action, pthread_mutex_lock(mutex)));
    else if (action == UNLOCK)
        return (print_if_error(action, pthread_mutex_unlock(mutex)));
    else if (action == DESTROY)
        return (print_if_error(action, pthread_mutex_destroy(mutex)));
    return (1);
}

int thread_do(int action, pthread_t *thread, void *(*routine)(void *), void *data)
{
    if (action == CREATE)
        return (print_if_error(action, pthread_create(thread, NULL, routine, data)));
    else if (action == JOIN)
        return (print_if_error(action, pthread_join(*thread, NULL)));
    else if (action == DETACH)
        return (print_if_error(action, pthread_detach(*thread)));
    return (1);
}
