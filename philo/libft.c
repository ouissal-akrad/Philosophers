/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:25:53 by ouakrad           #+#    #+#             */
/*   Updated: 2023/06/13 19:31:40 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

long	sequal(int i, char *str, int sign)
{
	long	value;

	value = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		value = value * 10 + str[i++] - '0';
		if ((value > 2147483647 && sign == 1) || (value > 2147483648 && sign
				== -1))
			ft_error();
	}
	if (str[i])
		ft_error();
	return (value * sign);
}

long	ft_atoi(char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (!str[i])
		ft_error();
	if (str[i] == '-')
		ft_error();
	else if (str[i] == '+')
		i++;
	if (!str[i])
		ft_error();
	return (sequal(i, str, sign));
}

// void	print(t_list *info)
// {
// 	int	i;

// 	i = 1;
// 	while (info)
// 	{
// 		printf("philo-->%d: philo_nbr %d\n", i, info->philo_nbr);
// 		printf("philo-->%d: time_to_die :%llu\n", i, info->time_to_die);
// 		printf("philo-->%d: time_to_eat :%llu\n", i, info->time_to_eat);
// 		printf("philo-->%d: time_to_sleep :%llu\n", i, info->time_to_sleep);
// 		printf("philo-->%d: eat_time_max :%llu\n", i, info->eat_time_max);
// 		i++;
// 		info = info->next;
// 	}
// }