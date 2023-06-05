/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:25:28 by ouakrad           #+#    #+#             */
/*   Updated: 2023/06/05 23:20:03 by ouakrad          ###   ########.fr       */
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

void	ft_printf(char *msg, t_list *philo)
{
	pthread_mutex_lock(&philo->ft_printf_mutex);
	printf("%lld %d %s\n", ft_get_time() - philo->start, philo->philo_nbr, msg);
	pthread_mutex_unlock(&philo->ft_printf_mutex);
}

void	death(t_list *philo)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->for_last_eat);
		if ((ft_get_time() - philo->last_eat) >= philo->time_to_die)
		{
			ft_printf("died", philo);
			pthread_mutex_lock(&philo->ft_printf_mutex);
			pthread_mutex_unlock(&philo->for_last_eat);
			break ;
		}
		pthread_mutex_unlock(&philo->for_last_eat);
		pthread_mutex_lock(&philo->for_n_meals);
		if ((philo->eat_time_max > 0) && philo->n_meals >= philo->eat_time_max
			&& philo->check == 0)
		{
			pthread_mutex_unlock(&philo->for_n_meals);
			philo->check = 1;
			i++;
			if (i >= philo->philo_nbr)
				break ;
		}
		pthread_mutex_unlock(&philo->for_n_meals);
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
		ft_printf("has taken a fork", philo);
		pthread_mutex_lock(&philo->next->fork);
		ft_printf("has taken a fork", philo);
		pthread_mutex_lock(&philo->for_last_eat);
		philo->last_eat = ft_get_time();
		pthread_mutex_unlock(&philo->for_last_eat);
		ft_printf("is eating", philo);
		pthread_mutex_lock(&philo->for_n_meals);
		philo->n_meals++;
		pthread_mutex_unlock(&philo->for_n_meals);
		my_usleep(philo->time_to_eat);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		ft_printf("is sleeping", philo);
		my_usleep(philo->time_to_sleep);
		ft_printf("is thinking", philo);
	}
	return (NULL);
}

t_list	*init_philo(int ac, char **av)
{
	t_list			*philo;
	int				i;
	int				philo_nbr;
	t_list			*temp;
	pthread_mutex_t	ft_printf_mutex;

	pthread_mutex_init(&ft_printf_mutex, NULL);
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
	while (i < philo_nbr)
	{
		temp->ft_printf_mutex = ft_printf_mutex;
		temp = temp->next;
		i++;
	}
	death(philo);
	// i = 0;
	// temp = philo;
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