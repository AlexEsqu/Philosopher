/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:35:00 by mkling            #+#    #+#             */
/*   Updated: 2024/11/26 14:04:15 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_if(bool condition, char *message, t_monitor *monitor)
{
	if (condition == false)
		return ;
	if (monitor != NULL)
		free(monitor);
	if (message != NULL)
		printf("%s\n", message);
	exit (1);
}

int	ft_atoi(const char *str)
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

int	ft_is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	return (0);
}

int	str_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_is_digit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	check_syntax(int argc, char **argv)
{
	int	i;

	exit_if(argc < 5, "Missing arguments", NULL);
	exit_if(argc > 6, "Too many arguments", NULL);
	i = 1;
	while (i < argc)
	{
		exit_if(!str_is_digit(argv[i]),
			"Inputs can only be digits", NULL);
		exit_if(i == NUMBER_OF_PHILOSOPHER && ft_atoi(argv[i]) == 0,
			"There must be at least one philosopher", NULL);
		exit_if(i == TIME_TO_DIE && ft_atoi(argv[i]) == 0,
			"Philosophers cannot die on the spot", NULL);
		exit_if(i == TIME_TO_EAT && ft_atoi(argv[i]) == 0,
			"Philosophers need some time to eat", NULL);
		exit_if((i == TIME_TO_SLEEP && ft_atoi(argv[i]) == 0),
			"Philosophers need some time to sleep", NULL);
		i++;
	}
}
