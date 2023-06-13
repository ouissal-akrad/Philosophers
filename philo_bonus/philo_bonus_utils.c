/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:40:57 by ouakrad           #+#    #+#             */
/*   Updated: 2023/06/13 19:16:29 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	ft_error(const char *message)
{
	fprintf(stderr, "Error: %s\n", message);
	exit(1);
}

void	ft_printf(char *msg, t_list *philo)
{
	sem_wait(philo->data->print);
	printf("%lld %d %s\n", ft_get_time() - philo->data->start, philo->index,
		msg);
	sem_post(philo->data->print);
}

void	waiting(t_list *philo)
{
	int	status;

	status = -1;
	while (waitpid(-1, &status, 0) > 0)
		kill_all_philo(philo);
}
