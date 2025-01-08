/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:35:26 by mkling            #+#    #+#             */
/*   Updated: 2025/01/09 00:08:27 by alex             ###   ########.fr       */
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

typedef struct s_waiter t_waiter;

enum e_argv {
	NUMBER_OF_PHILOSOPHER	= 1,
	TIME_TO_DIE				= 2,
	TIME_TO_EAT				= 3,
	TIME_TO_SLEEP			= 4,
	NUMBER_OF_MEALS			= 5
};

enum e_philo_states {
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
};

enum e_mtx_thd_actions {
	INIT,
	LOCK,
	UNLOCK,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
	MALLOC,
};

enum e_time {
	SECONDS,
	MILLISECONDS,
	MICROSECONDS,
};

typedef struct s_fork {
	int			fork_id;
	t_mutex		fork;
}	t_fork;

typedef struct s_philo {
	int			id;
	int			is_sated;
	int			meal_count;
	int			last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_mutex		philo_mutex;
	pthread_t	thread;
	t_waiter	*waiter;
}	t_philo;

typedef struct s_waiter {
	int			is_end;
	int			is_ready;
	int			philo_total;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			max_meals;
	int			start_time;
	t_philo		**philo_array;
	t_fork		**fork_array;
	t_mutex		table_mutex;
	t_mutex		write_mutex;
}	t_waiter;

/* PARSING */

int		parse_for_waiter(int argc, char **argv, t_waiter *waiter);

/* INITIALIZATION */

int		set_table(t_waiter *waiter);
void	wait_on_philosophers(t_waiter *waiter);


int		write_status(int status, t_philo *philo, bool debug);


/* UTILS */

int		setter(t_mutex *mutex, int *destination, int value);
int		getter(t_mutex *mutex, int *value);
size_t	get_miliseconds(void);
void	micro_usleep(size_t wait_time, t_waiter *waiter);
bool 	dinner_has_ended(t_waiter *waiter);


/* ERROR HANDLING */

int		thread_do(int action, pthread_t *thread, void *(*routine)(void *), void *data);
int		mutex_do(int action, t_mutex *mutex);
int		print_if_error(int action, int status);



// int		create_philo(t_waiter *monitor);
// int		wait_on_philo(t_waiter *monitor);
// void	*routine(void *);
// size_t	get_miliseconds(t_waiter *monitor);
// void	clean_up(t_waiter *monitor);

#endif
