/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:11:38 by fbouteil          #+#    #+#             */
/*   Updated: 2025/03/14 11:11:40 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_starvation(t_philo *philo)
{
	long int		timestamp;
	int				i;

	i = 0;
	pthread_mutex_lock(&philo->meal_mutex);
	timestamp = get_millis() - philo->table->start_time;
	if ((timestamp - philo->last_meal) >= philo->table->time_to_die)
	{
		pthread_mutex_lock(&philo->table->simu_mutex);
		philo->table->simu_on = 0;
		pthread_mutex_unlock(&philo->table->simu_mutex);
		pthread_mutex_lock(&philo->table->message_mutex);
		printf(RED "%ld %i died\n" RESET,
			timestamp,
			philo->id);
		pthread_mutex_unlock(&philo->table->message_mutex);
		pthread_mutex_unlock(&philo->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	return (0);
}

int	check_meals(t_philo *philos)
{
	int				i;

	i = 0;
	if (philos->table->meals_to_fullfilment == -1)
		return (0);
	while (i < philos->table->philo_count)
	{
		pthread_mutex_lock(&philos[i].meal_mutex);
		if (philos[i].number_of_meals < philos->table->meals_to_fullfilment)
			return (pthread_mutex_unlock(&philos[i].meal_mutex), 0);
		pthread_mutex_unlock(&philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_lock(&philos->table->simu_mutex);
	philos->table->simu_on = 0;
	pthread_mutex_unlock(&philos->table->simu_mutex);
	return (1);
}

void	*watch(void *arg)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)arg;
	while (1)
	{
		i = 0;
		usleep(50);
		while (i < philos->table->philo_count)
		{
			if (check_starvation(&philos[i]))
				return (NULL);
			i++;
		}
		if (check_meals(philos))
		{
			pthread_mutex_lock(&philos->table->message_mutex);
			printf("Philosophers full. Simulation done !\n");
			pthread_mutex_unlock(&philos->table->message_mutex);
			return (NULL);
		}
	}
	return (NULL);
}
