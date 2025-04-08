/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:14:16 by fbouteil          #+#    #+#             */
/*   Updated: 2025/03/13 14:14:17 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleep_message(t_philo *philo)
{
	long	timestamp;

	pthread_mutex_lock(&philo->table->message_mutex);
	pthread_mutex_lock(&philo->table->simu_mutex);
	if (philo->table->simu_on == 0)
		return (pthread_mutex_unlock(&philo->table->simu_mutex),
			pthread_mutex_unlock(&philo->table->message_mutex), 1);
	pthread_mutex_unlock(&philo->table->simu_mutex);
	timestamp = get_millis() - philo->table->start_time;
	printf(CYAN "%ld %i is sleeping\n" RESET, timestamp, philo->id);
	pthread_mutex_unlock(&philo->table->message_mutex);
	return (0);
}

int	eat_message(t_philo *philo)
{
	long	timestamp;

	pthread_mutex_lock(&philo->table->message_mutex);
	pthread_mutex_lock(&philo->table->simu_mutex);
	if (philo->table->simu_on == 0)
		return (pthread_mutex_unlock(&philo->table->simu_mutex),
			pthread_mutex_unlock(&philo->table->message_mutex), 1);
	pthread_mutex_unlock(&philo->table->simu_mutex);
	timestamp = get_millis() - philo->table->start_time;
	printf(YELLOW "%ld %i is eating\n" RESET, timestamp, philo->id);
	pthread_mutex_unlock(&philo->table->message_mutex);
	return (0);
}

int	think_message(t_philo *philo)
{
	long	timestamp;

	pthread_mutex_lock(&philo->table->message_mutex);
	pthread_mutex_lock(&philo->table->simu_mutex);
	if (philo->table->simu_on == 0)
		return (pthread_mutex_unlock(&philo->table->simu_mutex),
			pthread_mutex_unlock(&philo->table->message_mutex), 1);
	pthread_mutex_unlock(&philo->table->simu_mutex);
	timestamp = get_millis() - philo->table->start_time;
	printf(MAGENTA "%ld %i is thinking\n" RESET, timestamp, philo->id);
	pthread_mutex_unlock(&philo->table->message_mutex);
	return (0);
}

int	fork_message(t_philo *philo)
{
	long	timestamp;

	pthread_mutex_lock(&philo->table->message_mutex);
	pthread_mutex_lock(&philo->table->simu_mutex);
	if (philo->table->simu_on == 0)
		return (pthread_mutex_unlock(&philo->table->simu_mutex),
			pthread_mutex_unlock(&philo->table->message_mutex), 1);
	pthread_mutex_unlock(&philo->table->simu_mutex);
	timestamp = get_millis() - philo->table->start_time;
	printf(GREEN "%ld %i has taken a fork\n" RESET, timestamp, philo->id);
	pthread_mutex_unlock(&philo->table->message_mutex);
	return (0);
}
