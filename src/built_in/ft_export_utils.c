/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:12:07 by seb               #+#    #+#             */
/*   Updated: 2025/03/24 11:59:28 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	is_valid(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (!strchr(str, '='))
		return (0);
	while (str[i])
	{
		if (str[i] != '_' && !ft_isalnum(str[i]) && str[i] != '=')
			return (0);
		i++;
	}
	return (1);
}
