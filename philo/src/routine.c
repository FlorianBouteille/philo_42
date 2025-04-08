/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:44:20 by fbouteil          #+#    #+#             */
/*   Updated: 2025/03/13 13:44:22 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	go_to_sleep(t_philo *philo)
{
	sleep_message(philo);
	micro_nap(philo, (long)philo->table->time_to_sleep);
}

void	eat(t_philo *philo)
{
	if (philo->id % 2 == 1)
		philo->got_forks += pick_up_fork(philo, philo->left_fork);
	philo->got_forks += 10 * pick_up_fork(philo, philo->right_fork);
	if (philo->id % 2 == 0)
		philo->got_forks += pick_up_fork(philo, philo->left_fork);
	if (philo->got_forks == 11)
	{
		eat_message(philo);
		pthread_mutex_lock(&philo->meal_mutex);
		philo->last_meal = get_millis() - philo->table->start_time;
		philo->number_of_meals++;
		pthread_mutex_unlock(&philo->meal_mutex);
		micro_nap(philo, (long)philo->table->time_to_eat);
	}
	if (philo->got_forks % 2 == 1)
		drop_fork(philo, philo->left_fork);
	if (philo->got_forks >= 10)
		drop_fork(philo, philo->right_fork);
	philo->got_forks = 0;
}

void	think(t_philo *philo)
{
	think_message(philo);
	usleep(1000);
}

int	pick_up_fork(t_philo *philo, int fork_id)
{
	pthread_mutex_lock(&philo->table->simu_mutex);
	if (philo->table->simu_on == 0)
		return (pthread_mutex_unlock(&philo->table->simu_mutex), 0);
	pthread_mutex_unlock(&philo->table->simu_mutex);
	pthread_mutex_lock(&philo->table->forks[fork_id]);
	fork_message(philo);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	i = 0;
	if (philo->table->philo_count == 1)
		return (lonely_thinker(philo), NULL);
	else if (philo->id % 2 == 0)
		even_routine(philo);
	else if (philo->id % 2 == 1)
		odd_routine(philo);
	return (NULL);
}
