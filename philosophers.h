#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>


typedef struct s_philo
{
	pthread_t				philo;
	pthread_mutex_t			fork;
	int						index;
	int						philo_nbr;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	unsigned long long int	eat_time_max;
	unsigned long long int  last_eat;
	unsigned long long int  start;
	unsigned long long int	n_meals;
	struct s_philo			*next;
}							t_list;

/*------------------libft-----------------*/
long						ft_atoi(char *str);
void						ft_error(void);
int							ft_isdigit(int c);
void						print(t_list *info);
t_list						*ft_lstnew(int ac, char **av);
void						ft_lstadd_back(t_list **lst, t_list *new);
t_list						*init_philo(int ac, char **av);
t_list	*ft_lstlast(t_list *lst);
int							ft_lstsize(t_list *lst);
void						*routine(void *arg);
unsigned long long ft_get_time();
#endif