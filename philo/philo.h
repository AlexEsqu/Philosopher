/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:35:26 by mkling            #+#    #+#             */
/*   Updated: 2024/11/26 16:40:39 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>

enum e_argv {
	NUMBER_OF_PHILOSOPHER	= 1,
	TIME_TO_DIE				= 2,
	TIME_TO_EAT				= 3,
	TIME_TO_SLEEP			= 4,
	NUMBER_OF_MEALS			= 5
};

typedef struct s_philo {
	int				id;
	int				last_meal;
	pthread_mutex_t	fork;
	pthread_t		thread;
}	t_philo;

typedef struct s_composium {
	int			philo_count;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			meal_count;
	t_philo		*philo;
}	t_monitor;


void	exit_if(bool condition, char *message, t_monitor *monitor);
int		ft_atoi(const char *str);
void	check_syntax(int argc, char **argv);
void	init_monitor(int argc, char **argv, t_monitor *monitor);
void	create_philo(t_monitor *monitor);
void	wait_on_philo(t_monitor *monitor);
void	*routine(void *);
size_t	get_miliseconds(t_monitor *monitor);
void	clean_up(t_monitor *monitor);

#endif
