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

int	printing_death(t_set *set)
{
	t_philosof		*ph;

	ph = set->philosof;
	pthread_mutex_lock(&(set->table->check));
	ft_putnbr_fd(timestamp() - set->or_time, 1);
	write(1, " ", 1);
	ft_putnbr_fd(ph->number, 1);
	write(1, " ", 1);
	ft_putstr_fd("has died", 1);
	write(1, "\n", 1);
	pthread_mutex_unlock(&(set->table->check));
	return (0);
}

int	printing(t_set *set, char *text)
{
	t_philosof		*ph;

	ph = set->philosof;
	if (!access_death(set))
	{
		pthread_mutex_lock(&(set->table->check));
		ft_putnbr_fd(timestamp() - set->or_time, 1);
		write(1, " ", 1);
		ft_putnbr_fd(ph->number, 1);
		write(1, " ", 1);
		ft_putstr_fd(text, 1);
		write(1, "\n", 1);
		pthread_mutex_unlock(&(set->table->check));
	}
	return (0);
}

int	check_n(t_set *set, int n)
{
	if (set->ar.limited == true)
	{
		if (n == set->ar.n_must_eat)
		{
			set->ate_all = true;
			return (1);
		}
	}
	return (0);
}

int	eat(t_set *set)
{
	int	n;

	n = 0;
	while (!access_death(set) && n <= set->ar.n_must_eat
		&& set->ate_all == false)
	{
		if (check_n(set, n))
			return (0);
		pthread_mutex_lock(&set->table->forks[set->philosof->left_fork]);
		printing(set, "has taken a fork");
		pthread_mutex_lock(&set->table->forks[set->philosof->right_fork]);
		printing(set, "has taken a fork");
		pthread_mutex_lock(&set->table->permit);
		printing(set, "is eating");
		set->philosof->last_meal = timestamp() - set->or_time;
		pthread_mutex_unlock(&set->table->permit);
		usleep(set->ar.t_to_eat * 1000);
		pthread_mutex_unlock(&set->table->forks[set->philosof->right_fork]);
		pthread_mutex_unlock(&set->table->forks[set->philosof->left_fork]);
		printing(set, "is sleeping");
		usleep(set->ar.t_to_sleep * 1000);
		printing(set, "is thinking");
		n++;
	}
	return (0);
}
