/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgreenpo <cgreenpo@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 09:08:15 by cgreenpo          #+#    #+#             */
/*   Updated: 2023/06/23 11:01:57 by cgreenpo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_free(void *data)
{
	if (data)
		free(data);
	data = NULL;
}

void	mod_death(t_set *set)
{
	pthread_mutex_lock(&(set->table->no_race));
	set->all->is_dead = true;
	pthread_mutex_unlock(&(set->table->no_race));
}

int	access_death(t_set *set)
{
	pthread_mutex_lock(&(set->table->no_race));
	if (set->all->is_dead == true)
	{
		pthread_mutex_unlock(&(set->table->no_race));
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&(set->table->no_race));
		return (0);
	}
}

int	access_status(t_set *set)
{
	pthread_mutex_lock(&(set->table->no_race));
	if (set->all->ate_all == true)
	{
		pthread_mutex_unlock(&(set->table->no_race));
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&(set->table->no_race));
		return (0);
	}
}
