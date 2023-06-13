/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:37:26 by ouakrad           #+#    #+#             */
/*   Updated: 2023/06/13 18:42:52 by ouakrad          ###   ########.fr       */
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

void	ft_close(t_list *philo)
{
	sem_close(philo->data->fork);
	sem_unlink("fork");
	sem_close(philo->data->print);
	sem_unlink("print");
}
