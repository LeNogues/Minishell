/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:46:43 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/05/21 16:09:52 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

static int	is_in_tab(char *str, char **cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str || !cmd)
		return (0);
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j++] == '=')
				return (0);
		}
		i++;
	}
	i = 0;
	while (cmd[i])
	{
		if (ft_strncmp(cmd[i], str, ft_strlen(cmd[i]) + 1) == -61)
			return (1);
		i++;
	}
	return (0);
}

static int	create_new_env(t_env *env, char **new_env, char **cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env->envp[i])
	{
		if (is_in_tab(env->envp[i], cmd) == 0)
		{
			new_env[j] = ft_strdup(env->envp[i]);
			if (!new_env[j])
			{
				free_tab(new_env);
				new_env = NULL;
				return (0);
			}
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (1);
}

void	ft_unset(char **cmd, t_env *env)
{
	char	**new_env;
	int		size;

	if (!env || !env->envp)
		return ;
	size = ft_tablen(env->envp) + 1;
	if (!cmd[1])
		return ;
	new_env = ft_calloc(sizeof(char *), size);
	if (!new_env)
		return ;
	if (!create_new_env(env, new_env, cmd))
		return ;
	free_tab(env->envp);
	set_environment(env, new_env);
	free_tab(new_env);
	return ;
}
