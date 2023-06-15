/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:20:49 by ouakrad           #+#    #+#             */
/*   Updated: 2023/06/14 22:22:51 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	philo->n_meals = 0;
	philo->check = 0;
	philo->start = ft_get_time();
	philo->last_eat = ft_get_time();
	pthread_mutex_init(&philo->fork, NULL);
	pthread_mutex_init(&philo->for_last_eat, NULL);
	pthread_mutex_init(&philo->for_n_meals, NULL);
	philo->next = NULL;
	if (ac == 6)
		philo->eat_time_max = ft_atoi(av[5]);
	else
		philo->eat_time_max = 0;
	return (philo);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!lst || !new)
	{
		return ;
	}
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
