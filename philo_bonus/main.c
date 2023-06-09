/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:25:28 by ouakrad           #+#    #+#             */
/*   Updated: 2023/06/09 17:54:04 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_free(t_list *philo, int philo_size)
{
	int		i;
	t_list	*tmp;

	tmp = philo;
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

void	*death(void *arg)
{
	t_list	*philo;

	philo = (t_list *)arg;
	// printf("start [%lld]\n", )
	while (1)
	{
		if (((ft_get_time()) - philo->last_eat) > (philo->time_to_die))
		{
			sem_wait(philo->print);
			printf("%lld %d died\n", ft_get_time() - philo->start,
					philo->index);
			exit(0);
		}
	}
	return (NULL);
}

void	kill_all_philo(t_list *philo)
{
	int	i;

	i = 0;
	while (philo)
	{
		kill(philo->pid, SIGKILL);
		philo = philo->next;
		if (philo->index == 1)
			return ;
	}
	ft_free(philo, philo->philo_nbr);
}

void	waiting(t_list *philo)
{
	while (waitpid(-1, &philo->status, 0) > 0)
	{
		if (philo->status == 0)
			kill_all_philo(philo);
	}
}

void	ft_routine(t_list *philo)
{
	pthread_create(&philo->philo, NULL, &death, philo);
	while (1)
	{
		sem_wait(philo->fork);
		sem_wait(philo->print);
		printf("%lld %d has taken a fork\n", ft_get_time() - philo->start,
				philo->index);
		sem_post(philo->print);
		sem_wait(philo->fork);
		sem_wait(philo->print);
		printf("%lld %d has taken a fork\n", ft_get_time() - philo->start,
				philo->index);
		sem_post(philo->print);
		sem_wait(philo->print);
		philo->last_eat = ft_get_time();
		printf("%lld %d is eating\n", ft_get_time() - philo->start,
				philo->index);
		sem_post(philo->print);
		my_usleep(philo->time_to_eat);
		sem_post(philo->fork);
		sem_post(philo->fork);
		if (philo->eat_time_max)
			philo->n_meals++;
		if (philo->eat_time_max && philo->eat_time_max <= philo->n_meals)
			exit(0);
		sem_wait(philo->print);
		printf("%lld %d is sleeping\n", ft_get_time() - philo->start,
				philo->index);
		sem_post(philo->print);
		my_usleep(philo->time_to_sleep);
		sem_wait(philo->print);
		printf("%lld %d is thinking\n", ft_get_time() - philo->start,
				philo->index);
		sem_post(philo->print);
	}
}

t_list	*init_philo(int ac, char **av)
{
	t_list	*philo;
	int		i;
	int		philo_nbr;

	philo = NULL;
	philo_nbr = atoi(av[1]);
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
	return (philo);
}

int	main(int ac, char **av)
{
	t_list *philo = NULL;
	int philo_nbr;
	if (ac < 5 || ac > 6)
		ft_error();
	int i = 0;
	philo_nbr = ft_atoi(av[1]);
	if (!philo_nbr)
		return (0);
	philo = init_philo(ac, av);
	if (!philo)
		return (0);
	t_list *temp = philo;
	time_t start = ft_get_time();
	while (i < philo_nbr)
	{
		temp->start = start;
		temp->pid = fork();
		if (temp->pid == -1)
			ft_error();
		else if (temp->pid == 0)
			ft_routine(temp);
		temp = temp->next;
		i++;
	}
	// exit(0);
	int status;
	while (waitpid(-1, &status, 0) > 0)
	{
		if (status == 0)
			kill_all_philo(philo);
	}
	// waiting(philo);
	sem_close(philo->fork);
	sem_unlink("fork");
	sem_close(philo->print);
	sem_unlink("print");
	return (0);
}