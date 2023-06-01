/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:25:28 by ouakrad           #+#    #+#             */
/*   Updated: 2023/06/01 19:36:33 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	valid_params(int ac, char **av)
{
	t_list	*info;

	info = malloc(sizeof(t_list));
	if (info == NULL)
		ft_error();
	info->philo_nbr = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		info->eat_time_max = ft_atoi(av[5]);
	else
		info->eat_time_max = 0;
	if (info->philo_nbr < 1 || info->time_to_die < 0 || info->time_to_eat < 0
		|| info->time_to_sleep < 0 || info->eat_time_max < 0)
		return (0);
	print(info);
	return (1);
}
int	main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		ft_error();
	if (!valid_params(ac, av))
		ft_error();
}