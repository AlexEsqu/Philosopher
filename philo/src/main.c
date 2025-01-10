/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:35:01 by mkling            #+#    #+#             */
/*   Updated: 2025/01/10 00:34:45 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool dinner_has_ended(t_waiter *waiter)
{
	return (getter(&waiter->table_mutex, &waiter->is_end) == true);
}

int	print_error(int error_code)
{
	if (error_code == ERR_MALLOC)
		printf("Malloc failed\n");
	if (error_code == ERR_MUTEX)
		printf("Mutex failed\n");
	if (error_code == ERR_THREAD)
		printf("Thread failed\n");
	else
		printf("Error");
	return (error_code);
}

int	main(int argc, char **argv)
{
	t_waiter	waiter;

	if (parse_for_waiter(argc, argv, &waiter) != 0)
		return (1);
	printf("Waiter is ready\n");
	if (set_table(&waiter) != 0)
		return (1);
	printf("Table is set\n");
	start_dinner(&waiter);
	return (0);
}
