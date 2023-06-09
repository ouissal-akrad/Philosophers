#ifndef PHILOS_BONUS_H
# define PHILOS_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pid_t			pid;
	pid_t			*pids;
	pthread_t		philo;
	sem_t			*fork;
	sem_t			*print;
	int				status;
	int				for_n_meals;
	int				for_last_eat;
	int				check;
	int				index;
	int				philo_nbr;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	long long int	eat_time_max;
	size_t			last_eat;
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
t_list				*init_philo(int ac, char **av);
t_list				*ft_lstlast(t_list *lst);
int					ft_lstsize(t_list *lst);
void				ft_routine(t_list *philo);
unsigned long long	ft_get_time(void);
void				ft_free(t_list *philo, int philo_size);
void				waiting(t_list *philo);
void				*death(void *arg);
void				kill_all_philo(t_list *philo);

#endif