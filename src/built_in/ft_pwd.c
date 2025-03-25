/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:45:28 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/03/24 13:41:05 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	ft_pwd(t_env *env)
{
	char	*current_path;

	if (!env)
		return (0);
	current_path = ft_getenv("PWD=", env);
	if (!current_path)
	{
		perror("getcwd");
		return (0);
	}
	write(1, current_path, strlen(current_path));
	write(1, "\n", 1);
	free(current_path);
	return (1);
}
