/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:37:51 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/04/02 17:40:43 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	set_environment(t_env *env, char **envp)
{
	int			i;
	const int	size = ft_tablen(envp) + 1;

	i = 0;
	if (!env || !envp)
		return (1);
	env->envp = malloc(sizeof(char *) * size);
	if (!env->envp)
		return (-1);
	while (envp[i])
	{
		env->envp[i] = ft_strdup(envp[i]);
		if (!env->envp[i])
		{
			free_tab(env->envp);
			return (-1);
		}
		i++;
	}
	env->envp[i] = NULL;
	return (0);
}

static int	create_env(t_env *env)
{
	env->envp = malloc(sizeof(char *) * 2);
	if (!env->envp)
		return (-1);
	env->envp[0] = ft_strjoin(ft_strdup("PWD="), getcwd(NULL, 0));
	if (!env->envp[0])
		return (-1);
	env->envp[1] = 0;
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	env = malloc(sizeof(t_env));
	handle_signal();
	if (!env)
		return (-1);
	if (!envp[0])
	{
		if (create_env(env))
			return (2);
	}
	else if (set_environment(env, envp))
		return (3);
	hub(env);
	free_tab(env->envp);
	free(env);
	return (0);
}
