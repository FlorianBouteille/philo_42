/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:05:29 by fbouteil          #+#    #+#             */
/*   Updated: 2025/03/13 12:05:38 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_watcher(pthread_t watcher, t_philo *philos)
{
	if (pthread_create(&watcher, NULL, &watch, philos) != 0)
		return (printf("failed to init watcher\n"), 1);
	return (0);
}

t_table	*init_table(int argc, char **argv)
{
	t_table	*table;
	int		i;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->start_time = get_millis();
	table->philo_count = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->meals_to_fullfilment = -1;
	table->simu_on = 1;
	pthread_mutex_init(&table->simu_mutex, NULL);
	pthread_mutex_init(&table->message_mutex, NULL);
	if (argc == 6)
		table->meals_to_fullfilment = ft_atoi(argv[5]);
	table->forks = malloc(table->philo_count * sizeof(pthread_mutex_t));
	if (!(table->forks))
		return (NULL);
	i = 0;
	while (i < table->philo_count)
		pthread_mutex_init(&table->forks[i++], NULL);
	return (table);
}

t_philo	*init_philos(t_table *table)
{
	t_philo	*philos;
	int		i;

	philos = malloc(table->philo_count * sizeof(t_philo));
	if (!philos)
		return (NULL);
	i = 0;
	while (i < table->philo_count)
	{
		philos[i].id = i + 1;
		philos[i].table = table;
		philos[i].number_of_meals = 0;
		philos[i].right_fork = i;
		philos[i].got_forks = 0;
		pthread_mutex_init(&philos[i].meal_mutex, NULL);
		if (i == 0)
			philos[i].left_fork = table->philo_count - 1;
		else
			philos[i].left_fork = i - 1;
		philos[i].last_meal = table->start_time;
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]) != 0)
			return (printf("Failed to create thread !\n"), NULL);
		i++;
	}
	return (philos);
}
