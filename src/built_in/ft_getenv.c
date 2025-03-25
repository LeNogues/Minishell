/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:28:59 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/03/24 13:40:29 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

char	*get_home(t_env *env)
{
	int	i;

	i = 0;
	if (!env || !env->envp)
		return (0);
	while (env->envp[i])
	{
		if (strncmp("HOME=", env->envp[i], 5) == 0)
			break ;
		i++;
	}
	if (!env->envp[i])
		return (0);
	return (env->envp[i] + 5);
}

char	*ft_getenv(char *value_name, t_env *env)
{
	int		i;
	char	*value_env;
	int		size_value_name;

	if (!env || !env->envp || !value_name)
		return (0);
	size_value_name = ft_strlen(value_name);
	i = 0;
	while (env->envp[i])
	{
		if (strncmp(value_name, env->envp[i], size_value_name) == 0)
			break ;
		i++;
	}
	if (env->envp[i])
		value_env = ft_strdup(env->envp[i] + size_value_name);
	else
		return (0);
	return (value_env);
}
