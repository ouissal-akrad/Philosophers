/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:25:53 by ouakrad           #+#    #+#             */
/*   Updated: 2023/06/09 18:06:04 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_list	*ft_lstnew(int ac, char **av)
{
	t_list	*philo;
	philo = malloc(sizeof(t_list));
	if (philo == NULL)
		return (NULL);
	philo->philo_nbr = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	philo->pids = malloc(philo->philo_nbr * sizeof(int));
	philo->start = ft_get_time();
	philo->last_eat = ft_get_time();
	philo->n_meals = 0;
	sem_unlink("fork");
	philo->fork = sem_open("fork", O_CREAT, 666, philo->philo_nbr);
	sem_unlink("print");
	philo->print = sem_open("print", O_CREAT, 666, 1);
	if (ac == 6)
		philo->eat_time_max = ft_atoi(av[5]);
	else
		philo->eat_time_max = 0;
	if (philo->philo_nbr < 1 || philo->time_to_die < 0 || philo->time_to_eat < 0
		|| philo->time_to_sleep < 0 || philo->eat_time_max < 0)
		return (NULL);
	return (philo);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!lst || !new)
		return ;
	tmp = *lst;
	if (!tmp)
	{
		new->next = *lst;
		*lst = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

void	ft_error(void)
{
	printf("ERROR!\n");
	exit(1);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

long	sequal(int i, char *str, int sign)
{
	long	value;

	value = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		value = value * 10 + str[i++] - '0';
		if ((value > 2147483647 && sign == 1) || (value > 2147483648 && sign ==
				-1))
			ft_error();
	}
	if (str[i])
		ft_error();
	return (value * sign);
}

long	ft_atoi(char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (!str[i])
		ft_error();
	if (str[i] == '-')
		ft_error();
	else if (str[i] == '+')
		i++;
	if (!str[i])
		ft_error();
	return (sequal(i, str, sign));
}

void	print(t_list *info)
{
	int	i;

	i = 1;
	while (info)
	{
		printf("philo-->%d: philo_nbr %d\n", i, info->philo_nbr);
		printf("philo-->%d: philo_index %d\n", i, info->index);
		printf("philo-->%d: time_to_die :%zu\n", i, info->time_to_die);
		printf("philo-->%d: time_to_eat :%zu\n", i, info->time_to_eat);
		printf("philo-->%d: time_to_sleep :%zu\n", i, info->time_to_sleep);
		printf("philo-->%d: eat_time_max :%lld\n", i, info->eat_time_max);
		i++;
		info = info->next;
	}
}