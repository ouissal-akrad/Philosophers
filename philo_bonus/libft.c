/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:25:53 by ouakrad           #+#    #+#             */
/*   Updated: 2023/06/12 19:40:28 by ouakrad          ###   ########.fr       */
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

t_list	*ft_lstnew(int index)
{
	t_list	*philo;

	philo = malloc(sizeof(t_list));
	if (!philo)
		return (NULL);
	philo->index = index;
	philo->next = NULL;
	philo->last_eat = ft_get_time();
	philo->n_meals = 0;
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
	t_list	*current;
	int		count;

	if (lst == NULL)
		return (0);
	current = lst;
	count = 0;
	while (1)
	{
		count++;
		current = current->next;
		if (current == lst)
			break ;
	}
	return (count);
}

void	ft_error(const char *message)
{
	fprintf(stderr, "Error: %s\n", message);
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
			ft_error("Invalid number of philosophers");
	}
	if (str[i])
		ft_error("Invalid number of philosophers");
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
		ft_error("Invalid number of philosophers");
	if (str[i] == '-')
		ft_error("Invalid number of philosophers");
	else if (str[i] == '+')
		i++;
	if (!str[i])
		ft_error("Invalid number of philosophers");
	return (sequal(i, str, sign));
}

// void	print(t_list *philo)
// {
// int	i;

// i = 1;
// while (philo)
// {
// 	printf("philo-->%d: philo_nbr %d\n", i, philo->data->philo_nbr);
// 	// printf("philo-->%d: philo_index %d\n", i, philo->datainfo->index);
// 	printf("philo-->%d: time_to_die :%zu\n", i, philo->data->time_to_die);
// 	printf("philo-->%d: time_to_eat :%zu\n", i, philo->data->time_to_eat);
// 	printf("philo-->%d: time_to_sleep :%zu\n", i, philo->data->time_to_sleep);
// 	printf("philo-->%d: eat_time_max :%zu\n", i, philo->data->eat_time_max);
// 	i++;
// 	philo = philo->next;
// }
// }
