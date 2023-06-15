/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:22:16 by ouakrad           #+#    #+#             */
/*   Updated: 2023/06/15 12:51:12 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	pthread_mutex_lock(philo->ft_printf_mutex);
	printf("%lld %d %s\n", ft_get_time() - philo->start, philo->index, msg);
	pthread_mutex_unlock(philo->ft_printf_mutex);
}

void	detach_all_threads(t_list *philo)
{
	t_list	*current;
	t_list	*start;

	current = philo;
	start = philo;
	while (1)
	{
		pthread_detach(current->philo);
		current = current->next;
		if (current == start)
			break ;
	}
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
