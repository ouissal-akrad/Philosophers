#ifndef PHILOS_BONUS_H
# define PHILOS_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

typedef struct s_data
{
	sem_t				*fork;
	sem_t				*print;
	int					philo_nbr;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	unsigned long long	eat_time_max;
	size_t				start;
}						t_data;

typedef struct s_philo
{
	int check;
	pid_t				pid;
	pthread_t			philo;
	int					status;
	int					index;
	unsigned long long	last_eat;
	unsigned long long	n_meals;
	t_data				*data;
	struct s_philo		*next;
}						t_list;

/*------------------libft-----------------*/
long					ft_atoi(char *str);
void					ft_error(void);
int						ft_isdigit(int c);
void					print(t_list *info);
t_list					*ft_lstnew(int index);
void					ft_lstadd_back(t_list **lst, t_list *new);
t_list					*init_philo(char **av);
t_list					*ft_lstlast(t_list *lst);
int						ft_lstsize(t_list *lst);
void					ft_routine(t_list *philo);
unsigned long long		ft_get_time(void);
void					ft_free(t_list *philo, int philo_size);
void					waiting(t_list *philo);
void					*death(void *arg);
t_data					*init_data(int ac, char **av);
void					kill_all_philo(t_list *philo);

#endif