/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:34:46 by fbouteil          #+#    #+#             */
/*   Updated: 2025/03/11 15:34:48 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN    "\033[36m"
# define RESET   "\033[0m"
# define MAX_PHILOSOPHERS	200

typedef struct s_table
{
	long			start_time;
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_to_fullfilment;
	int				simu_on;
	pthread_mutex_t	*forks;
	pthread_mutex_t	simu_mutex;
	pthread_mutex_t	message_mutex;
}	t_table;

typedef struct s_philo
{
	int				id;
	int				right_fork;
	int				left_fork;
	int				got_forks;
	pthread_t		thread;
	t_table			*table;
	long int		last_meal;
	int				number_of_meals;
	pthread_mutex_t	meal_mutex;	
}	t_philo;

int		ft_atoi(char *str);
t_table	*init_table(int argc, char **argv);
t_philo	*init_philos(t_table *table);
void	*routine(void *arg);
void	even_routine(t_philo *philo);
void	odd_routine(t_philo *philo);
void	lonely_thinker(t_philo *philo);
long	get_millis(void);
int		micro_nap(t_philo *philo, long int time);
int		sleep_message(t_philo *philo);
int		eat_message(t_philo *philo);
int		think_message(t_philo *philo);
int		fork_message(t_philo *philo);
void	go_to_sleep(t_philo *philo);
void	eat(t_philo *philo);
void	think(t_philo *philo);
int		pick_up_fork(t_philo *philo, int fork_id);
void	drop_fork(t_philo *philo, int fork_id);
int		init_watcher(pthread_t watcher, t_philo *philos);
void	*watch(void *arg);
void	clear_before_exit(t_philo *philo);
int		check_startvation(t_philo philo);
int		check_meals(t_philo *philo);
int		is_numeric(char c);
int		min(int a, int b);
int		max(int a, int b);

#endif
