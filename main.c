/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:25:28 by ouakrad           #+#    #+#             */
/*   Updated: 2023/06/03 17:18:23 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *param)
{
	t_list	*philo;

	philo = (t_list *)param;
	while (philo->philo_nbr)
	{
		if (philo->philo_nbr % 2 == 0)
			usleep(philo->time_to_eat * 1000);
		pthread_mutex_lock(&philo->fork);
		printf("%d has taken a fork\n", philo->philo_nbr);
		pthread_mutex_lock(&philo->next->fork);
		printf("%d has teken a fork\n", philo->philo_nbr);
		printf("%d is eating\n", philo->philo_nbr);
		usleep(philo->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		printf("%d is sleeping\n", philo->philo_nbr);
		usleep(philo->time_to_sleep * 1000);
		printf("%d is thinking\n", philo->philo_nbr);
	}
	return (NULL);
}

t_list	*init_philo(int ac, char **av)
{
	t_list	*philo;
	int		i;
	int		philo_nbr;
	t_list	*temp;

	philo = NULL;
	philo_nbr = ft_atoi(av[1]);
	i = 0;
	while (i < philo_nbr)
	{
		ft_lstadd_back(&philo, ft_lstnew(ac, av));
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
	i = 0;
	temp = philo;
	while (i < philo_nbr)
	{
		pthread_join(temp->philo, NULL);
		temp = temp->next;
		i++;
	}
	// print(philo);
	return (philo);
}

int	main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		ft_error();
	if (!init_philo(ac, av))
		return (0);
}