/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:25:28 by ouakrad           #+#    #+#             */
/*   Updated: 2023/06/13 22:31:50 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	mutex_destroy(t_list *philo)
// {
// 	pthread_mutex_destroy(philo->ft_printf_mutex);
// 	while (philo)
// 	{
// 		pthread_mutex_destroy(&philo->fork);
// 		philo = philo->next;
// 		if (philo->index == 1)
// 			break ;
// 	}
// 	ft_free(philo,philo->philo_nbr);
// }

void	init_philo_2(t_list *philo, int philo_nbr)
{
	t_list			*temp;
	pthread_mutex_t	ft_printf_mutex;
	int				i;

	pthread_mutex_init(&ft_printf_mutex, NULL);
	i = 0;
	temp = philo;
	while (i < philo_nbr)
	{
		temp->ft_printf_mutex = &ft_printf_mutex;
		temp = temp->next;
		i++;
	}
	i = 0;
	temp = philo;
	while (i < philo_nbr)
	{
		pthread_create(&(temp->philo), NULL, &routine, temp);
		temp = temp->next;
		i++;
	}
	death(philo);
}

void	*init_philo(int ac, char **av)
{
	t_list	*philo;
	int		i;
	int		philo_nbr;

	philo = NULL;
	philo_nbr = ft_atoi(av[1]);
	if (!philo_nbr)
		return (NULL);
	i = 0;
	while (i < philo_nbr)
	{
		ft_lstadd_back(&philo, ft_lstnew(ac, av));
		ft_lstlast(philo)->index = i + 1;
		i++;
	}
	ft_lstlast(philo)->next = philo;
	init_philo_2(philo, philo_nbr);
	return (NULL);
}

int	main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		ft_error();
	init_philo(ac, av);
	return (0);
}
