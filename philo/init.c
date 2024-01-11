/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgreenpo <cgreenpo@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 09:08:15 by cgreenpo          #+#    #+#             */
/*   Updated: 2021/06/23 11:01:57 by cgreenpo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_set	*init_set(t_ar ar, t_table *table, t_philosof *ph, t_unit *all)
{
	int		i;
	t_set	*set;

	set = malloc(sizeof (t_set) * ar.num_of_ph);
	i = 0;
	while (i < ar.num_of_ph)
	{
		set[i].philosof = &ph[i];
		set[i].ar = ar;
		set[i].table = table;
		set[i].or_time = 0;
		set[i].all = all;
		set[i].ate_all = false;
		i++;
	}
	return (set);
}

void	init_last(t_philosof *philosof, int i)
{
	if (i == 0)
	{
		philosof[i].left_fork = 0;
		philosof[i].right_fork = 1;
	}
	else
	{
		philosof[i].right_fork = 0;
		philosof[i].left_fork = i;
	}
	philosof[i].number = i + 1;
	philosof[i].is_dead = false;
}

t_philosof	*init_philo(t_ar ar)
{
	t_philosof	*philosof;
	int			i;

	i = 0;
	philosof = malloc(sizeof(t_philosof) * (ar.num_of_ph + 1));
	while (i < ar.num_of_ph)
	{
		if (i == ar.num_of_ph - 1)
		{
			init_last(philosof, i);
			break ;
		}
		else
		{
			philosof[i].number = i + 1;
			philosof[i].left_fork = i;
			philosof[i].is_dead = false;
			philosof[i].right_fork = i + 1;
			i++;
		}
	}
	return (philosof);
}

t_ar	init_ar(int argc, char **argv)
{
	t_ar	ar;

	ar.num_of_ph = ft_atoi(argv[1]);
	ar.t_to_die = ft_atoi(argv[2]) + 5;
	ar.t_to_eat = ft_atoi(argv[3]);
	ar.t_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		ar.n_must_eat = ft_atoi(argv[5]);
		ar.limited = true;
	}
	else
	{
		ar.limited = false;
		ar.n_must_eat = 1;
	}
	return (ar);
}

t_table	*init_table(t_ar ar)
{
	t_table		*table;
	int			i;

	i = 0;
	table = (t_table *)malloc(sizeof(t_table));
	while (i < ar.num_of_ph)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&table->permit, NULL);
	pthread_mutex_init(&table->check, NULL);
	pthread_mutex_init(&table->no_race, NULL);
	return (table);
}
