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

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	*go(void *args)
{
	t_set	*set;

	set = (t_set *)args;
	if (set->philosof->number % 2 == 0)
		usleep(15000);
	while (!access_death(set) && set->ate_all == false)
		eat(set);
	return (NULL);
}

int	start(t_set *set, int n)
{
	int			i;
	pthread_t	*threads;
	pthread_t	check;
	long long	t;

	i = 0;
	threads = malloc(sizeof(pthread_t) * n);
	pthread_create(&check, NULL, (void *(*)(void *))check_death,
		(void *)&set[i]);
	t = timestamp();
	while (i < n)
	{
		set[i].or_time = t;
		pthread_create(&threads[i], NULL, (void *(*)(void *))go,
			(void *)&set[i]);
		i++;
	}
	while (--i >= 0)
	{
		pthread_join(threads[i], NULL);
	}
	pthread_detach(check);
	free(threads);
	return (0);
}

int	program_exit(t_table *table, t_set *set, t_philosof *ph)
{
	int	i;

	i = 0;
	while (i < set[i].ar.num_of_ph)
	{
		pthread_mutex_destroy(&(table->forks[i]));
		i++;
	}
	i = 0;
	pthread_mutex_destroy(&(table->permit));
	pthread_mutex_destroy(&(table->check));
	pthread_mutex_destroy(&(table->no_race));
	my_free(table);
	my_free(set[i].all);
	my_free(ph);
	my_free(set);
	return (0);
}

int	main(int argc, char **argv)
{
	t_ar		ar;
	t_philosof	*philosof;
	t_table		*table;
	t_set		*set;
	t_unit		*all;

	if (argc != 5 && argc != 6)
		return (0);
	all = malloc(sizeof(t_unit));
	all->is_dead = false;
	all->ate_all = false;
	ar = init_ar(argc, argv);
	philosof = init_philo(ar);
	table = init_table(ar);
	set = init_set(ar, table, philosof, all);
	if (ar.num_of_ph == 1)
	{
		set->or_time = timestamp();
		all->is_dead = true;
		death(set);
	}
	start(set, ar.num_of_ph);
	return (program_exit(table, set, philosof));
}
