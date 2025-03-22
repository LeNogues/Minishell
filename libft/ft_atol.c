/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:11:05 by seb               #+#    #+#             */
/*   Updated: 2025/03/22 15:11:46 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	convert_string_to_long(const char *str, long *result, int sign)
{
	long	check_overflow;

	check_overflow = 0;
	*result = 0;
	while (*str >= '0' && *str <= '9')
	{
		*result = *result * 10 + (*str - '0');
		if (*result < check_overflow)
			return (-1);
		check_overflow = *result;
		str++;
	}
	*result *= sign;
	return (1);
}

long	ft_atol(const char *str, long *result)
{
	int	sign;

	sign = 1;
	*result = 0;
	if (!str)
		return (1);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	if (convert_string_to_long(str, result, sign) == -1)
		return (-1);
	while (*str >= '0' && *str <= '9')
		str++;
	if (*str != '\0')
	{
		*result = 2;
		return (-1);
	}
	return (1);
}
