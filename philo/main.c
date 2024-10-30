/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:35:01 by mkling            #+#    #+#             */
/*   Updated: 2024/10/30 19:57:24 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	exit_if(bool condition, char *message)
{
	if (condition == false)
		return ;
	if (message != NULL)
		printf("%s\n", message);
	exit (1);
}

size_t	get_miliseconds(void)
{
	struct timeval	time;

	exit_if((gettimeofday(&time, NULL) == -1), "gettimeofday error");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	check_syntax(int argc, char **argv)
{
	int	i;

	exit_if(argc < 4, "Missing arguments");
	exit_if(argc > 5, "Too many arguments");
	i = 1;
	while (i < argc)
	{
		exit_if(ft_atoi(argv[i]) == 0
			&& i != NUMBER_OF_MEALS, "Argument cannot be 0");
		while (*argv[i]++)
			exit_if(!ft_is_digit(*argv[i]), "Non digit as arguments");
	}
}

int	main(int argc, char **argv)
{
	check_syntax(argc, argv);
	return (0);
}
