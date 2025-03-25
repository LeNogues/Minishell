/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:02:12 by sle-nogu          #+#    #+#             */
/*   Updated: 2024/11/17 12:30:39 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}
/*
int main()
{
	char null_char;

	null_char = 0;
	printf("TEST");

	printf("string tester : Bonjour correcteur\n");
	printf("valeur attendu : 18\n");
	printf("valeur retourne : %zu\n\n", ft_strlen("Bonjour correcteur"));

	printf("string tester : 12\n");
	printf("valeur attendu : 2\n");
	printf("valeur retourne : %zu\n\n", ft_strlen("12"));

	printf("string tester : "     "\n");
	printf("valeur attendu : 5\n");
	printf("valeur retourne : %zu\n\n", ft_strlen("     "));

	printf("string tester : ""\n");
	printf("valeur attendu : 0\n");
	printf("valeur retourne : %zu\n\n", ft_strlen(&null_char));

	printf("string tester : b\n");
	printf("valeur attendu : 1\n");
	printf("valeur retourne : %zu\n\n", ft_strlen("b"));
}*/
