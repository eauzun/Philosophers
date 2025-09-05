/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:29:01 by emuzun            #+#    #+#             */
/*   Updated: 2025/09/05 13:29:42 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	size_t	i;
	int		sign;
	int		res;

	res = 0;
	i = 0;
	sign = 1;
	while (str[i] && (str[i] == ' ' || (str[i] > 8 && str[i] < 14)))
		i++;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		if (str[i++] == '-')
			sign = -sign;
	while (str[i] && str[i] >= 48 && str[i] <= 57)
		res = (res * 10) + ((str[i++] - 48) * sign);
	return (res);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}
