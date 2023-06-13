/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:20:14 by ouakrad           #+#    #+#             */
/*   Updated: 2023/06/13 22:49:35 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		philo;
	pthread_mutex_t	fork;
	pthread_mutex_t	for_n_meals;
	pthread_mutex_t	for_last_eat;
	int				check;
	int				index;
	int				philo_nbr;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	long long int	eat_time_max;
	size_t			last_eat;
	pthread_mutex_t	*ft_printf_mutex;
	size_t			start;
	int				n_meals;
	struct s_philo	*next;
}					t_list;

/*------------------libft-----------------*/
long				ft_atoi(char *str);
void				ft_error(void);
int					ft_isdigit(int c);
void				print(t_list *info);
t_list				*ft_lstnew(int ac, char **av);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				*init_philo(int ac, char **av);
t_list				*ft_lstlast(t_list *lst);
int					ft_lstsize(t_list *lst);
void				*routine(void *arg);
unsigned long long	ft_get_time(void);
void				ft_free(t_list *philo, int philo_size);
void				death(t_list *philo);
void				ft_printf(char *msg, t_list *philo);
void				my_usleep(unsigned long long time);
unsigned long long	ft_get_time(void);
int					helper(t_list *philo);
void				sleeping(t_list *philo);
void				ft_free(t_list *philo, int philo_size);
void				init_philo_2(t_list *philo, int philo_nbr);
#endif