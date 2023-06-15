/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:56:31 by ouakrad           #+#    #+#             */
/*   Updated: 2023/06/15 12:51:33 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_all_philo(t_list *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->philo_nbr)
	{
		kill(philo->data->pid_table[i], SIGKILL);
		i++;
	}
}

void	*death(void *arg)
{
	t_list	*philo;

	philo = (t_list *)arg;
	while (1)
	{
		pthread_mutex_lock(&(philo->data->for_last_eat));
		if ((ft_get_time() - philo->last_eat) > philo->data->time_to_die)
		{
			sem_wait(philo->data->print);
			printf("%lld %d died\n", ft_get_time() - philo->data->start,
				philo->index);
			exit(1);
		}
		pthread_mutex_unlock(&(philo->data->for_last_eat));
		usleep(1000);
	}
	return (NULL);
}

void	ft_routine(t_list *philo)
{
	pthread_create(&philo->philo, NULL, &death, philo);
	while (1)
	{
		sem_wait(philo->data->fork);
		ft_printf("has taken a fork", philo);
		sem_wait(philo->data->fork);
		ft_printf("has taken a fork", philo);
		pthread_mutex_lock(&(philo->data->for_last_eat));
		philo->last_eat = ft_get_time();
		pthread_mutex_unlock(&(philo->data->for_last_eat));
		ft_printf("is eating", philo);
		my_usleep(philo->data->time_to_eat);
		sem_post(philo->data->fork);
		sem_post(philo->data->fork);
		if (philo->data->eat_time_max)
			philo->n_meals++;
		if (philo->data->eat_time_max
			&& philo->data->eat_time_max <= philo->n_meals)
			exit(0);
		ft_printf("is sleeping", philo);
		my_usleep(philo->data->time_to_sleep);
		ft_printf("is thinking", philo);
	}
}
