#ifndef PHILOS_H
# define PHILOS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

// pthread_mutex_t ft_printf_mutex; // Mutex for ft_printf

typedef struct s_philo
{
	pthread_t				philo;
	pthread_mutex_t			fork;
	pthread_mutex_t			for_n_meals;
	pthread_mutex_t			for_last_eat;
	int						check;
	int						index;
	int						philo_nbr;
	unsigned long long int	time_to_die;
	unsigned long long int	time_to_eat;
	unsigned long long int	time_to_sleep;
	long long int			eat_time_max;
	unsigned long long int	last_eat;
	pthread_mutex_t 		*ft_printf_mutex;
	unsigned long long int	start;
	int						n_meals;
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
t_list						*ft_lstlast(t_list *lst);
int							ft_lstsize(t_list *lst);
void						*routine(void *arg);
unsigned long long			ft_get_time(void);
void						ft_free(t_list *philo, int philo_size);

#endif