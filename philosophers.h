#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>

typedef struct data
{
	int	philo_nbr;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eat_time_max;
}		t_list;

/*------------------libft-----------------*/
long	ft_atoi(char *str);
void	ft_error(void);
int		ft_isdigit(int c);
void	print(t_list *info);
#endif