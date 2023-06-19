/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:25:28 by ouakrad           #+#    #+#             */
/*   Updated: 2023/06/19 11:37:57 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_list	*init_philo(char **av)
{
	t_list	*philo;
	int		i;
	int		philo_nbr;

	philo = NULL;
	philo_nbr = atoi(av[1]);
	if (philo_nbr <= 0)
		return (NULL);
	i = 0;
	while (i < philo_nbr)
	{
		ft_lstadd_back(&philo, ft_lstnew(i + 1));
		i++;
	}
	ft_lstlast(philo)->next = philo;
	return (philo);
}

t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->eat_time_max = 0;
	data->philo_nbr = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->eat_time_max = ft_atoi(av[5]);
	if (data->philo_nbr < 1 || data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0 || (data->eat_time_max <= 0 && ac == 6))
		ft_error("Invalid argument");
	sem_unlink("fork");
	sem_unlink("print");
	data->fork = sem_open("fork", O_CREAT, 666, data->philo_nbr);
	if (data->fork == SEM_FAILED)
		printf("fatal error : could not create semaphores\n");
	data->print = sem_open("print", O_CREAT, 666, 1);
	if (data->print == SEM_FAILED)
		printf("fatal error : could not create semaphores\n");
	return (data);
}

void	ft_fork(char **av, t_list *philo, t_data *data)
{
	int		philo_nbr;
	int		i;
	pid_t	pid;

	philo_nbr = ft_atoi(av[1]);
	if (philo_nbr <= 0)
		ft_error("Invalid number of philosophers");
	i = 0;
	while (i < philo_nbr)
	{
		philo->data = data;
		pid = fork();
		if (pid == -1)
			ft_error("Fork failed");
		if (pid == 0)
			ft_routine(philo);
		data->pid_table[i] = pid;
		philo = philo->next;
		i++;
	}
}

int	main(int ac, char **av)
{
	t_list	*philo;
	t_data	*data;

	if (ac < 5 || ac > 6)
		ft_error("Invalid number of arguments");
	philo = init_philo(av);
	data = init_data(ac, av);
	philo->data = data;
	data->pid_table = malloc(data->philo_nbr * sizeof(pid_t));
	if (!data->pid_table)
		return (0);
	philo->data->start = ft_get_time();
	ft_fork(av, philo, data);
	waiting(philo);
	ft_close(philo);
	// while(1);
	return (0);
}
