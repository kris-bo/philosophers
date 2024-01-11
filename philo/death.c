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

int	death(t_set	*set)
{
	t_philosof		*ph;
	long long		c;

	ph = set->philosof;
	c = timestamp() - set->or_time - ph->last_meal;
	if (set->ate_all == false && c >= set->ar.t_to_die
		|| set->ar.num_of_ph == 1)
	{
		set->is_dead = true;
		mod_death(set);
		printing_death(set);
		return (1);
	}
	return (0);
}

void	*check_death(void *args)
{
	t_set	*set;
	int		i;

	set = args;
	i = 0;
	while (1)
	{
		usleep(10000);
		while (i < set[0].ar.num_of_ph)
		{
			if (death(&set[i]))
			{
				return (NULL);
			}
			i++;
			if (i == set[0].ar.num_of_ph)
				i = 0;
		}
	}
}
