/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgreenpo <cgreenpo@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 09:08:15 by cgreenpo          #+#    #+#             */
/*   Updated: 2021/10/23 11:01:57 by cgreenpo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static unsigned long	ft_result(const char *str, size_t *i, int *sign)
{
	unsigned long	nbr;
	unsigned long	limit;

	nbr = 0;
	limit = 9223372036854775807 / 10;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		if (nbr >= limit && *sign == 1)
			return (-1);
		else if (nbr >= limit && *sign == -1)
			return (0);
		nbr = nbr * 10 + (str[(*i)++] - '0');
	}
	return (nbr);
}

int	ft_atoi(const char *str)
{
	size_t			i;
	int				sign;

	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	return ((int)(ft_result(str, &i, &sign) * sign));
}
