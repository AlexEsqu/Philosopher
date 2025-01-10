/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:35:00 by mkling            #+#    #+#             */
/*   Updated: 2025/01/10 00:01:45 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* To avoid trying to convert a number higher than INT MAX,
but still attempt conversion of smaller numbers with prefixed spaces or 0 */
static bool	is_too_long_for_int(char *str)
{
	int	digit_count;

	digit_count = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\r' || *str == '\f' || *str == '\v')
		str++;
	if (*str == '-' || *str == '+')
		str++;
	while ((*str) == '0')
		str++;
	while ((*str >= '0' && *str <= '9'))
	{
		digit_count++;
		str++;
	}
	return (digit_count > 10);
}

/* Ignores whitespace, accepts one sign, then converts characters into int */
static int	ft_atoi(const char *str)
{
	int	i;
	int	minus;
	int	number;

	i = 0;
	minus = -1;
	number = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			minus = minus * (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 - (str[i] - '0');
		i++;
	}
	return (number * minus);
}

/* Checks that input is only comprized of digits, signs or spaces */
static int	str_is_digit_sign_or_space(char *str)
{
	while (*str)
	{
		if ((*str >= '0' && *str <= '9') || (*str == ' '))
			str++;
		else if (*str == '+' || *str == '-')
			str++;
		else
			return (0);
	}
	return (1);
}

/* Return NULL if correct, otherwise the specified error message
Checks input is between 5 and 6, only digits, and fits the */
static int	check_syntax(int argc, char **argv)
{
	int	i;

	if (argc < 5)
		return (printf("Missing arguments\n"));
	if (argc > 6)
		return (printf("Too many arguments\n"));
	i = 1;
	while (i < argc)
	{
		if (!str_is_digit_sign_or_space(argv[i]))
			return (printf("Input contains non digits\n"));
		if (is_too_long_for_int(argv[i]))
			return (printf("Input is too high! :leaf_emoji:\n"));
		i++;
	}
	return (0);
}

/*Check that input values are in the correct syntax & positive digits
Convert them into integers and loads them into the waiter struct */
int	parse_for_waiter(int argc, char **argv, t_waiter *waiter)
{
	if (check_syntax(argc, argv) != 0)
		return (1);
	waiter->philo_total = ft_atoi(argv[NUMBER_OF_PHILOSOPHER]);
	waiter->time_to_die = ft_atoi(argv[TIME_TO_DIE]);
	waiter->time_to_eat = ft_atoi(argv[TIME_TO_EAT]);
	waiter->time_to_sleep = ft_atoi(argv[TIME_TO_SLEEP]);
	if (argc == 6)
		waiter->max_meals = ft_atoi(argv[NUMBER_OF_MEALS]);
	else
		waiter->max_meals = -1;
	if (waiter->philo_total <= 0 || waiter->time_to_sleep <= 0
		|| waiter->time_to_die <= 0 || waiter->time_to_eat <= 0
		|| (argc == 6 && waiter->max_meals <= 0))
	{
		printf("Inputs cannot be null or negative\n");
		return (1);
	}
	return (0);
}
