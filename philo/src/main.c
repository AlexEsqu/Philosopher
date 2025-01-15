/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:35:01 by mkling            #+#    #+#             */
/*   Updated: 2025/01/15 14:14:53 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	dinner_has_ended(t_waiter *waiter)
{
	return (getter(&waiter->waiter_mutex, &waiter->is_dinner_ongoing) != true);
}

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
	waiter->start_time = get_miliseconds();
	if (waiter->start_time == 0)
		return (print_error(ERR_TIME));
	setter(&waiter->waiter_mutex, &waiter->is_dinner_ongoing, true);
	return (SUCCESS);
}

int	stop_dinner(t_waiter *waiter)
{
	int	i;

	i = 0;
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
