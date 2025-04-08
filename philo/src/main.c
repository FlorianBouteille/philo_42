/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:47:42 by fbouteil          #+#    #+#             */
/*   Updated: 2025/03/13 11:47:53 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char *argv[])
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (printf("Wrong number of arguments\n"), 1);
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!is_numeric(argv[i][j]))
				return (printf("Invalid argument : %s\n", argv[i]), 1);
			j++;
		}
		if (ft_atoi(argv[i]) < 1)
			return (printf("Invalid argument : %s\n", argv[i]), 1);
		i++;
	}	
	if (ft_atoi(argv[1]) > MAX_PHILOSOPHERS)
		return (printf("Too many philosophers\n"), 1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_table		*table;
	t_philo		*philos;
	pthread_t	watcher;
	int			i;

	if (check_args(argc, argv) != 0)
		return (1);
	table = init_table(argc, argv);
	if (!table)
		return (1);
	philos = init_philos(table);
	if (!philos)
		return (1);
	i = 0;
	pthread_create(&watcher, NULL, &watch, philos);
	while (i < table->philo_count)
	{
		if (pthread_join(philos[i++].thread, NULL) != 0)
			return (printf("Failed to join thread\n"), 1);
	}
	pthread_join(watcher, NULL);
	clear_before_exit(philos);
	return (0);
}
