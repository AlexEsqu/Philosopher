/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:35:01 by mkling            #+#    #+#             */
/*   Updated: 2025/01/13 13:41:08 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	dinner_has_ended(t_waiter *waiter)
{
	return (getter(&waiter->waiter_mutex, &waiter->is_dinner_ongoing) == true);
}

int	main(int argc, char **argv)
{
	t_waiter	waiter;

	if (parse_for_waiter(argc, argv, &waiter) != 0)
		return (1);
	printf("Waiter is set\n");
	if (set_table(&waiter) != 0)
		return (1);
	printf("Table is set\n");
	start_dinner(&waiter);
	clean_up(&waiter);
	return (0);
}
