/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:25:28 by ouakrad           #+#    #+#             */
/*   Updated: 2023/06/03 21:18:34 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	my_usleep(unsigned long long time)
{
	unsigned long long	start_time;

	start_time = ft_get_time();
	while ((ft_get_time() - start_time) > time)
		usleep(100);
}

void	*routine(void *param)
{
	t_list	*philo;

	philo = (t_list *)param;
	while (philo)
	{
		pthread_mutex_lock(&philo->fork);
		printf("%lld %d has taken a fork\n", ft_get_time() - philo->start, philo->index);
		pthread_mutex_lock(&philo->next->fork);
		printf("%lld %d has teken a fork\n", ft_get_time() - philo->start, philo->index);
		philo->last_eat = ft_get_time() - philo->start;
		printf("%lld %d is eating\n", ft_get_time() - philo->start, philo->index);
		my_usleep(philo->time_to_eat);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		if (philo->eat_time_max)
			philo->n_meals++;
		if (philo->eat_time_max && philo->eat_time_max <= philo->n_meals)
			break ;
		printf("%lld %d is sleeping\n", ft_get_time() - philo->start, philo->index);
		my_usleep(philo->time_to_sleep);
		printf("%lld %d is thinking\n", ft_get_time() - philo->start, philo->index);
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
		ft_lstlast(philo)->index = i + 1;
		i++;
	}
	pthread_mutex_init(&philo->fork, NULL);
	ft_lstlast(philo)->next = philo;
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