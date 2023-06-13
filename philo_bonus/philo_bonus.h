/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:18:52 by ouakrad           #+#    #+#             */
/*   Updated: 2023/06/13 19:18:56 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data
{
	sem_t				*fork;
	sem_t				*print;
	int					philo_nbr;
	pid_t				*pid_table;
	pthread_mutex_t		for_n_meals;
	pthread_mutex_t		for_last_eat;
	pthread_mutex_t		death;

	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	unsigned long long	eat_time_max;
	unsigned long long	start;
}						t_data;

typedef struct s_philo
{
	int					check;
	pid_t				pid;
	pthread_t			philo;
	int					status;
	int					index;
	unsigned long long	last_eat;
	unsigned long long	n_meals;
	t_data				*data;
	struct s_philo		*next;
}						t_list;

t_list					*ft_lstnew(int index);
t_list					*ft_lstlast(t_list *lst);
void					ft_lstadd_back(t_list **lst, t_list *new);
int						ft_isdigit(int c);
long					ft_atoi(char *str);
void					ft_printf(char *msg, t_list *philo);
void					ft_error(const char *message);
t_list					*init_philo(char **av);
void					kill_all_philo(t_list *philo);
void					ft_routine(t_list *philo);
unsigned long long		ft_get_time(void);
void					ft_free(t_list *philo, int philo_size);
void					waiting(t_list *philo);
void					*death(void *arg);
t_data					*init_data(int ac, char **av);
void					ft_close(t_list *philo);
void					ft_fork(char **av, t_list *philo, t_data *data);
unsigned long long		ft_get_time(void);
void					my_usleep(unsigned long long time);
void					waiting(t_list *philo);

#endif