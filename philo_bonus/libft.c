/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:31:57 by ouakrad           #+#    #+#             */
/*   Updated: 2023/06/19 15:30:21 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
			ft_error("Invalid number");
	}
	if (str[i])
		ft_error("Invalid number");
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
		ft_error("Invalid number");
	if (str[i] == '-')
		ft_error("Invalid number");
	else if (str[i] == '+')
		i++;
	if (!str[i])
		ft_error("Invalid number");
	return (sequal(i, str, sign));
}
