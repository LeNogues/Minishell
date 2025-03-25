/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sebastienlenogues@gmail.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:30:22 by sle-nogu          #+#    #+#             */
/*   Updated: 2024/11/17 18:43:37 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_strlen_spe(long n)
{
	int	size;

	size = 0;
	if (n < 0)
		size++;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		size++;
		n = n / 10;
	}
	return (size);
}

char	*is_zero(void)
{
	char	*number;

	number = ft_calloc(sizeof(char), 2);
	number[0] = '0';
	return (number);
}	

char	*ft_itoa(int n)
{
	char	*number;
	int		i;
	long	n_bis;

	i = 0;
	n_bis = n;
	if (n_bis == 0)
		return (is_zero());
	number = ft_calloc(sizeof(char), ft_strlen_spe(n_bis) + 1);
	if (!number)
		return (0);
	number[ft_strlen_spe(n)] = 0;
	i = ft_strlen_spe(n_bis);
	if (n_bis < 0)
	{
		number[0] = '-';
		n_bis = -n_bis;
	}
	while (n_bis != 0)
	{
		number[i - 1] = (n_bis % 10) + 48;
		n_bis = n_bis / 10;
		i--;
	}
	return (number);
}
/*
int main(int argc, char **argv)
{
	(void) argc;
	printf("%s\n", ft_itoa(atoi(argv[1])));
}*/
