/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:25:28 by ouakrad           #+#    #+#             */
/*   Updated: 2023/06/13 17:58:40 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_free(t_list *philo, int philo_size)
{
	int		i;
	t_list	*tmp;

	tmp = philo;
	i = 0;
	if (philo == NULL)
		return ;
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

void	kill_all_philo(t_list *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->philo_nbr)
	{
		kill(philo->data->pid_table[i], SIGKILL);
		i++;
	}
	//free(philo->data->pid_table);
	// ft_free(philo,philo->data->philo_nbr);
}

void	waiting(t_list *philo)
{
	int	status;

	status = -1;
	while (waitpid(-1, &status, 0) > 0)
		kill_all_philo(philo);
}

void	ft_printf(char *msg, t_list *philo)
{
	sem_wait(philo->data->print);
	printf("%lld %d %s\n", ft_get_time() - philo->data->start, philo->index,
			msg);
	sem_post(philo->data->print);
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

// void	ft_routine(t_list *philo)
// {
// 	pthread_create(&philo->philo, NULL, &death, philo);
// 	while (1)
// 	{
// 		sem_wait(philo->data->fork);
// 		sem_wait(philo->data->print);
// 		printf("%lld %d has taken a fork\n", ft_get_time() - philo->data->start,
// 				philo->index);
// 		sem_post(philo->data->print);
// 		sem_wait(philo->data->fork);
// 		sem_wait(philo->data->print);
// 		printf("%lld %d has taken a fork\n", ft_get_time() - philo->data->start,
// 				philo->index);
// 		sem_post(philo->data->print);
// 		sem_wait(philo->data->print);
// 		pthread_mutex_lock(&(philo->data->for_last_eat));
// 		philo->last_eat = ft_get_time();
// 		pthread_mutex_unlock(&(philo->data->for_last_eat));
// 		printf("%lld %d is eating\n", ft_get_time() - philo->data->start,
// 				philo->index);
// 		sem_post(philo->data->print);
// 		my_usleep(philo->data->time_to_eat);
// 		sem_post(philo->data->fork);
// 		sem_post(philo->data->fork);
// 		if (philo->data->eat_time_max)
// 			philo->n_meals++;
// 		if (philo->data->eat_time_max
// 			&& philo->data->eat_time_max <= philo->n_meals)
// 			exit(0);
// 		sem_wait(philo->data->print);
// 		printf("%lld %d is sleeping\n", ft_get_time() - philo->data->start,
// 				philo->index);
// 		sem_post(philo->data->print);
// 		my_usleep(philo->data->time_to_sleep);
// 		sem_wait(philo->data->print);
// 		printf("%lld %d is thinking\n", ft_get_time() - philo->data->start,
// 				philo->index);
// 		sem_post(philo->data->print);
// 	}
// }

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

t_list	*init_philo(char **av)
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
	data->philo_nbr = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->eat_time_max = ft_atoi(av[5]);
	else
		data->eat_time_max = 0;
	if (data->philo_nbr < 1 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0 || data->eat_time_max < 0)
		ft_error("Invalid argument");
	pthread_mutex_init(&(data->for_last_eat), NULL);
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

void	hh(void)
{
	printf("exit pid:%d\n", getpid());
	fflush(stdout);
}

int	main(int ac, char **av)
{
	// atexit(hh);
	t_list *philo = NULL;
	t_data *data;
	int philo_nbr;
	if (ac < 5 || ac > 6)
		ft_error("Invalid number of arguments");
	int i = 0;
	philo_nbr = ft_atoi(av[1]);
	if (!philo_nbr)
		ft_error("Invalid number of philosophers");
	philo = init_philo(av);
	if (!philo)
		return (0);
	data = init_data(ac, av);
	philo->data = data;
	philo->data->start = ft_get_time();
	data->pid_table = malloc(data->philo_nbr * sizeof(pid_t));
	t_list *next = NULL;
	while (i < philo_nbr)
	{
		next = philo->next;
		philo->data = data;
		pid_t pid = fork();
		if (pid == -1)
			ft_error("Fork failed");
		if (pid == 0)
			ft_routine(philo);
		data->pid_table[i] = pid;
		philo = philo->next;
		i++;
	}
	waiting(philo);
	sem_close(data->fork);
	sem_unlink("fork");
	sem_close(data->print);
	sem_unlink("print");
	return (0);
}