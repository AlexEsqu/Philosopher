/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:35:01 by mkling            #+#    #+#             */
/*   Updated: 2025/01/16 10:05:54 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_dinner(t_waiter *waiter)
{
	int	i;

	if (waiter->philo_total == 1)
		return (lonely_dinner(waiter->philo_array[0]));
	i = 0;
	while (i < waiter->philo_total)
	{
		if (pthread_create(&waiter->philo_array[i]->thread,
				NULL, dine, waiter->philo_array[i]) != 0)
			return (print_error(ERR_THREAD));
		i++;
	}
	micro_usleep(10, waiter);
	if (set_start_time(waiter) != 0)
		return (ERR_GENERAL);
	setter(&waiter->waiter_mutex, &waiter->is_on, true);
	return (SUCCESS);
}

int	stop_dinner(t_waiter *waiter)
{
	int	i;

	i = 0;
	usleep(10);
	while (i < waiter->philo_total)
		pthread_join(waiter->philo_array[i++]->thread, NULL);
	pthread_mutex_destroy(&waiter->waiter_mutex);
	pthread_mutex_destroy(&waiter->write_mutex);
	free_waiter(waiter);
	return (0);
}

int	main(int argc, char **argv)
{
	t_waiter	waiter;

	if (parse_for_waiter(argc, argv, &waiter) != 0)
		return (ERR_GENERAL);
	if (set_table(&waiter) != 0)
		return (ERR_GENERAL);
	if (start_dinner(&waiter) != 0)
		return (ERR_GENERAL);
	if (check_if_starving_or_sated(&waiter) != 0)
		return (ERR_GENERAL);
	stop_dinner(&waiter);
	return (SUCCESS);
}
