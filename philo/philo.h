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

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>

struct	s_philosof;

typedef struct s_ar
{
	int		num_of_ph;
	int		t_to_die;
	int		t_to_eat;
	int		t_to_sleep;
	int		n_must_eat;
	bool	limited;
}	t_ar;

typedef struct table_tag
{
	pthread_mutex_t	forks[200];
	pthread_mutex_t	permit;
	pthread_mutex_t	check;
	pthread_mutex_t	no_race;
}	t_table;

typedef struct s_unit{
	bool	is_dead;
	bool	ate_all;
}	t_unit;

typedef struct s_set
{
	struct s_philosof	*philosof;
	t_ar				ar;
	t_table				*table;
	long long			or_time;
	bool				is_dead;
	t_unit				*all;
	bool				ate_all;
}	t_set;

typedef struct s_philosof
{
	int				number;
	int				left_fork;
	int				right_fork;
	bool			is_dead;
	long long		last_meal;
	long long		check_time;
	struct s_set	*set;
}	t_philosof;

int			eat(t_set *set);
int			death(t_set	*set);
int			ft_atoi(const char *str);
long long	timestamp(void);
void		init_last(t_philosof *philosof, int i);
t_philosof	*init_philo(t_ar ar);
t_ar		init_ar(int argc, char **argv);
t_table		*init_table(t_ar ar);
t_set		*init_set(t_ar ar, t_table *table, t_philosof *ph, t_unit *all);
int			death(t_set	*set);
void		*check_death(void *args);
int			printing(t_set *set, char *text);
int			printing_death(t_set *set);
void		ft_putnbr_fd(int nb, int fd);
void		ft_putstr_fd(char *s, int fd);
char		*ft_strdup(const char *s1);
void		mod_death(t_set *set);
int			access_death(t_set *set);
int			access_status(t_set *set);
void		my_free(void *data);

#endif
