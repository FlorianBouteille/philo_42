/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:02:33 by fbouteil          #+#    #+#             */
/*   Updated: 2025/03/13 16:02:47 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	drop_fork(t_philo *philo, int fork_id)
{
	pthread_mutex_unlock(&philo->table->forks[fork_id]);
}

void	lonely_thinker(t_philo *philo)
{
	long int	timestamp;

	fork_message(philo);
	usleep(philo->table->time_to_die * 1000);
	timestamp = get_millis() - philo->table->start_time;
	pthread_mutex_lock(&philo[0].meal_mutex);
	philo[0].last_meal = 0;
	pthread_mutex_unlock(&philo[0].meal_mutex);
	return ;
}

void	odd_routine(t_philo *philo)
{
	int	i;
	int	simu_running;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->table->simu_mutex);
		simu_running = philo->table->simu_on;
		pthread_mutex_unlock(&philo->table->simu_mutex);
		if (!simu_running)
			break ;
		if (i % 3 == 0)
			think(philo);
		else if (i % 3 == 1)
			eat(philo);
		else if (i % 3 == 2)
			go_to_sleep(philo);
		i++;
	}
}

void	even_routine(t_philo *philo)
{
	int	i;
	int	simu_running;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->table->simu_mutex);
		simu_running = philo->table->simu_on;
		pthread_mutex_unlock(&philo->table->simu_mutex);
		if (!simu_running)
			break ;
		if (i % 3 == 0)
			eat(philo);
		else if (i % 3 == 1)
			go_to_sleep(philo);
		else if (i % 3 == 2)
			think(philo);
		i++;
	}
}
