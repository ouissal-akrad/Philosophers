/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:22:16 by ouakrad           #+#    #+#             */
/*   Updated: 2023/06/13 20:58:09 by ouakrad          ###   ########.fr       */
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

void	ft_error(void)
{
	printf("ERROR!\n");
	exit(1);
}

void	ft_free(t_list *philo, int philo_size)
{
	int		i;
	t_list	*tmp;

	tmp = philo;
	if (philo == NULL)
		return ;
	i = 0;
	while (i < philo_size)
	{
		tmp = philo->next;
		free(philo);
		philo = tmp;
		i++;
	}
}

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
