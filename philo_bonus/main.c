/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:25:28 by ouakrad           #+#    #+#             */
/*   Updated: 2023/06/08 20:08:54 by ouakrad          ###   ########.fr       */
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

// void	ft_printf(char *msg, t_list *philo)
// {
// 	pthread_mutex_lock(philo->ft_printf_mutex);
// 	printf("%lld %d %s\n", ft_get_time() - philo->start, philo->index, msg);
// 	pthread_mutex_unlock(philo->ft_printf_mutex);
// }

void *death(void *arg)
{
	(void)arg;
	return(NULL);
}

void	ft_routine(t_list *philo)
{
	while (1)
	{
		sem_wait(philo->fork);
		printf("%lld %d has taken a fork\n", ft_get_time() - philo->start, philo->index);
		sem_wait(philo->fork);
		printf("%lld %d has taken a fork\n", ft_get_time() - philo->start, philo->index);
		philo->last_eat = ft_get_time();
		printf("%lld %d is eating\n", ft_get_time() - philo->start, philo->index);
		my_usleep(philo->time_to_eat);
		sem_post(philo->fork);
		sem_post(philo->fork);
		if (philo->eat_time_max)
			philo->n_meals++;
		if (philo->eat_time_max && philo->eat_time_max <= philo->n_meals)
			exit(0);
		printf("%lld %d is sleeping\n", ft_get_time() - philo->start, philo->index);
		my_usleep(philo->time_to_sleep);
		printf("%lld %d is thinking\n", ft_get_time() - philo->start, philo->index);
	}
}

t_list *init_philo(int ac, char **av)
{
    t_list *philo = NULL;
    int i;
    int philo_nbr;

    philo_nbr = atoi(av[1]);
    if (!philo_nbr)
        return NULL;
    i = 0;
    while (i < philo_nbr)
    {
        ft_lstadd_back(&philo, ft_lstnew(ac, av));
        ft_lstlast(philo)->index = i + 1;
        i++;
    }
    ft_lstlast(philo)->next = philo;
    return philo;
}

int main(int ac, char **av)
{
    t_list *philo = NULL;
    if (ac < 5 || ac > 6)
        ft_error();
	int i = 0;
    philo = init_philo(ac, av);
    if (!philo)
        return 0;
    t_list *temp = philo;
    while (i < philo->philo_nbr)
    {
        philo->pid = fork();
        i++;
        temp = temp->next;
        if(philo->pid == 0)
        	pthread_create(&philo->philo, NULL, &death, &philo);
    }
    if(philo->pid == 0)
        ft_routine(philo);
	sem_close(philo->fork);
	sem_unlink("forks");
	sem_close(philo->print);
	sem_unlink("print");
	return(0);
}