/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:36:56 by fbouteil          #+#    #+#             */
/*   Updated: 2025/03/13 11:37:11 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_numeric(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	max(int a, int b)
{
	if (a < b)
		return (b);
	return (a);
}

int	ft_atoi(char *str)
{
	long int	nb;
	int			i;
	int			sign;

	i = 0;
	nb = 0;
	sign = 1;
	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] && is_numeric(str[i]))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb > 2147483647 || nb < -2147483648)
		return (-1);
	return ((int)nb * sign);
}

void	clear_before_exit(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->table->philo_count - 1)
		pthread_mutex_destroy(&philos->table->forks[i++]);
	i = 0;
	while (i < philos->table->philo_count)
		pthread_mutex_destroy(&philos[i++].meal_mutex);
	pthread_mutex_destroy(&philos->table->simu_mutex);
	pthread_mutex_destroy(&philos->table->message_mutex);
	free(philos->table->forks);
	free(philos->table);
	free(philos);
}
