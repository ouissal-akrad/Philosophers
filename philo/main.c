/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:25:28 by ouakrad           #+#    #+#             */
/*   Updated: 2023/06/15 10:56:50 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_list *philo, int philo_size)
{
	int		i;
	t_list	*tmp;

	i = 0;
	while (i < philo_size)
	{
		tmp = philo->next;
		free(philo);
		philo = tmp;
		i++;
	}
}

void	detach_all_threads(t_list *philo)
{
	t_list	*current;
	t_list	*start;

	current = philo;
	start = philo;
	int index = 0;
	while (1)
	{
		index++;
		pthread_detach(current->philo);
		current = current->next;
		if (current == start)
			break ;
	}
	ft_free(philo, philo->philo_nbr);
}

void	mutex_destroy(t_list *philo)
{
	int		index;
	int		size;

	index = 0;
	size = philo->philo_nbr;
	pthread_mutex_destroy(philo->ft_printf_mutex);
	while (index < size)
	{
		pthread_mutex_destroy(&philo->fork);
		index++;
		philo = philo->next;
	}
	detach_all_threads(philo);
}

void	init_philo_2(t_list *philo, int philo_nbr)
{
	t_list			*temp;
	pthread_mutex_t	*ft_printf_mutex;
	int				i;

	ft_printf_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(ft_printf_mutex, NULL);
	i = 0;
	temp = philo;
	while (i < philo_nbr)
	{
		temp->ft_printf_mutex = ft_printf_mutex;
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
	detach_all_threads(philo);
	mutex_destroy(philo);
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

int	check(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac > 6)
		return (write(2, "Error: too many arguments.\n", 28));
	if (ac < 5)
		return (write(2, "Error: too few arguments.\n", 27));
	while (i < ac)
	{
		if (ft_atoi(av[i]) <= 0)
			return (write(2, "Error: Invalid number.\n", 23));
		i++;
	}
	return (0);
}

void f()
{
	system("leaks philo");
}

int	main(int ac, char **av)
{
	atexit(f);
	if (check(ac, av))
		return (0);
	init_philo(ac, av);
	return (0);
}
