/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:20:56 by ouakrad           #+#    #+#             */
/*   Updated: 2023/06/13 22:49:50 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	helper(t_list *philo)
{
	pthread_mutex_lock(&philo->for_last_eat);
	if ((ft_get_time() - philo->last_eat) > philo->time_to_die)
	{
		pthread_mutex_lock(philo->ft_printf_mutex);
		printf("%lld %d died\n", ft_get_time() - philo->start,
			philo->philo_nbr);
		pthread_mutex_unlock(&philo->for_last_eat);
		// ft_free(philo, philo->philo_nbr);
		return (1);
	}
	pthread_mutex_unlock(&philo->for_last_eat);
	return (0);
}

void	death(t_list *philo)
{
	int	i;

	i = 0;
	while (1)
	{
		if (helper(philo))
		{
			break ;
			// ft_free(philo, philo->philo_nbr);
		}
		pthread_mutex_lock(&philo->for_n_meals);
		if ((philo->eat_time_max > 0) && philo->n_meals >= philo->eat_time_max
			&& philo->check == 0)
		{
			pthread_mutex_unlock(&philo->for_n_meals);
			philo->check = 1;
			i++;
			if (i >= philo->philo_nbr)
			{
				// ft_free(philo, philo->philo_nbr);
				break ;
			}
		}
		pthread_mutex_unlock(&philo->for_n_meals);
		philo = philo->next;
	}
}

// void	death(t_list *philo)
// {
// 	int	i;

// 	i = 0;
// 	while (1)
// 	{
// 		pthread_mutex_lock(&philo->for_last_eat);
// 		if ((ft_get_time() - philo->last_eat) > philo->time_to_die)
// 		{
// 			pthread_mutex_lock(philo->ft_printf_mutex);
// 			printf("%lld %d died\n", ft_get_time() - philo->start,
// 					philo->philo_nbr);
// 			pthread_mutex_unlock(&philo->for_last_eat);
// 			ft_free(philo, philo->philo_nbr);
// 			break ;
// 		}
// 		pthread_mutex_unlock(&philo->for_last_eat);
// 		pthread_mutex_lock(&philo->for_n_meals);
// 		if ((philo->eat_time_max > 0) && philo->n_meals >= philo->eat_time_max
// 			&& philo->check == 0)
// 		{
// 			pthread_mutex_unlock(&philo->for_n_meals);
// 			philo->check = 1;
// 			i++;
// 			if (i >= philo->philo_nbr)
// 			{
// 				ft_free(philo, philo->philo_nbr);
// 				break ;
// 			}
// 		}
// 		pthread_mutex_unlock(&philo->for_n_meals);
// 		philo = philo->next;
// 	}
// }

void	sleeping(t_list *philo)
{
	ft_printf("is sleeping", philo);
	my_usleep(philo->time_to_sleep);
}

void	*routine(void *arg)
{
	t_list	*philo;

	philo = (t_list *)arg;
	if (philo->index % 2 == 0)
		usleep(100);
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
		sleeping(philo);
		ft_printf("is thinking", philo);
	}
	return (NULL);
}
