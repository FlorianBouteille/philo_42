/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:19:05 by fbouteil          #+#    #+#             */
/*   Updated: 2025/03/13 14:19:08 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_millis(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	micro_nap(t_philo *philo, long int time)
{
	long int	start;
	int			simu_running;		

	start = get_millis();
	while (get_millis() - start <= time)
	{
		usleep(450);
		pthread_mutex_lock(&philo->table->simu_mutex);
		simu_running = philo->table->simu_on;
		pthread_mutex_unlock(&philo->table->simu_mutex);
		if (!simu_running)
			return (1);
	}
	return (0);
}
