/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:30:20 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/03/24 13:40:19 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	cd_home(t_env *env, char **path)
{
	char	*env_line;

	env_line = ft_getenv("HOME=", env);
	if (!env_line)
		env_line = NULL;
	*path = ft_strdup(env_line);
	if (!*path)
	{
		free(*path);
		free(env_line);
		return (write(1, "HOME not set\n", 13), 0);
	}
	free(env_line);
	return (1);
}
