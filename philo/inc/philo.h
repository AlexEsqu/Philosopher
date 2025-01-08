/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:35:26 by mkling            #+#    #+#             */
/*   Updated: 2025/01/08 20:33:34 by alex             ###   ########.fr       */
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
# include <errno.h>

# define t_mutex 	pthread_mutex_t

enum e_argv {
	NUMBER_OF_PHILOSOPHER	= 1,
	TIME_TO_DIE				= 2,
	TIME_TO_EAT				= 3,
	TIME_TO_SLEEP			= 4,
	NUMBER_OF_MEALS			= 5
};

enum e_mutex_action {
	INIT,
	LOCK,
	UNLOCK,
	DESTROY,
};

typedef	struct s_fork {
	int			fork_id;
	t_mutex		fork;
}	t_fork;

typedef struct s_philo {
	int				id;
	bool			sated;
	size_t			meal_count;
	long			last_meal_time;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread_id;
	t_waiter		*waiter;
}	t_philo;

typedef struct s_waiter {
	int			philo_count;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			meal_count;
	long		start_time;
	long		end_time;
	t_philo		**philo_array;
	t_fork		**fork_array
}	t_waiter;

int		parse_for_waiter(int argc, char **argv, t_waiter *waiter);
int		create_philo(t_waiter *monitor);
int		wait_on_philo(t_waiter *monitor);
void	*routine(void *);
size_t	get_miliseconds(t_waiter *monitor);
void	clean_up(t_waiter *monitor);

#endif
