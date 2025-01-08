/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:35:01 by mkling            #+#    #+#             */
/*   Updated: 2025/01/09 00:09:36 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool dinner_has_ended(t_waiter *waiter)
{
	return (getter(&waiter->table_mutex, &waiter->is_end) == true);
}

int	main(int argc, char **argv)
{
	t_waiter	waiter;

	if (parse_for_waiter(argc, argv, &waiter) != 0)
		return (1);
	if (set_table(&waiter) != 0)
		return (1);
	return (0);
}
