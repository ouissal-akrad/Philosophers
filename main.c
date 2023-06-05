/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:25:28 by ouakrad           #+#    #+#             */
/*   Updated: 2023/06/05 16:10:32 by ouakrad          ###   ########.fr       */
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
	while ((ft_get_time() - start_time) < time)
		usleep(100);
}

void	death(t_list *philo)
{
	int	i;

	while (1)
	{
		i = 0;
		if ((ft_get_time() - philo->last_eat) >= philo->time_to_die)
		{
			printf("%lld %d died\n", ft_get_time() - philo->start,
					philo->philo_nbr);
			break ;
		}
		if ((philo->eat_time_max > 0) && philo->n_meals >= philo->eat_time_max)
		{
			i++;
			if (i >= philo->eat_time_max)
				break ;
		}
		philo = philo->next;
	}
}

void	*routine(void *arg)
{
	t_list	*philo;

	philo = (t_list *)arg;
	if (philo->index % 2 == 0)
		my_usleep(philo->time_to_eat);
	while (philo)
	{
		pthread_mutex_lock(&philo->fork);
		printf("%lld %d has taken a fork\n", ft_get_time() - philo->start,
				philo->index);
		pthread_mutex_lock(&philo->next->fork);
		printf("%lld %d has teken a fork\n", ft_get_time() - philo->start,
				philo->index);
		philo->last_eat = ft_get_time();
		printf("%lld %d is eating\n", ft_get_time() - philo->start,
				philo->index);
		philo->n_meals++;
		my_usleep(philo->time_to_eat);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		// if (philo->eat_time_max && philo->eat_time_max <= philo->n_meals)
		// 	break ;
		printf("%lld %d is sleeping\n", ft_get_time() - philo->start,
				philo->index);
		my_usleep(philo->time_to_sleep);
		printf("%lld %d is thinking\n", ft_get_time() - philo->start,
				philo->index);
	}
	return (NULL);
}

t_list	*init_philo(int ac, char **av)
{
	t_list	*philo;
	int		i;
	int		philo_nbr;
	t_list	*temp;
	int		*n_meals;

	n_meals = 0;
	philo = NULL;
	philo_nbr = ft_atoi(av[1]);
	i = 0;
	while (i < philo_nbr)
	{
		ft_lstadd_back(&philo, ft_lstnew(ac, av));
		ft_lstlast(philo)->index = i + 1;
		i++;
	}
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
	death(philo);
	// while (i < philo_nbr)
	// {
	// 	pthread_join(temp->philo, NULL);
	// 	temp = temp->next;
	// 	i++;
	// }
	return (philo);
}

int	main(int ac, char **av)
{
	t_list *philo;
	if (ac < 5 || ac > 6)
		ft_error();
	philo = init_philo(ac, av);
	if (!philo)
		return (0);
}