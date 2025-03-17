/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   main.c                                               ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/03/12 12:37:51 by sle-nogu             │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/17 17:57:36 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

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

int	create_env(t_env *env)
{
	env->envp = malloc(sizeof(char *) * 3);
	if (!env->envp)
		return (-1);
	env->envp[0] = ft_strjoin(ft_strdup("PWD="), getcwd(NULL, 0));
	if (!env->envp[0])
		return (-1);
	env->envp[1] = ft_strjoin(ft_strdup("OLDPWD="), getcwd(NULL, 0));
	if (!env->envp[1])
	{
		free(env->envp[0]);
		free(env->envp);
		return (-1);
	}
	env->envp[2] = 0;
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	cmd;
	t_env	*env;
	long	result;

	(void)argc;
	(void)argv;
	cmd.cmd = NULL;
	env = malloc(sizeof(t_env));
	if (!env)
		return (-1);
	if (!envp[0])
	{
		if (create_env(env))
			return (2);
	}
	else if (set_environment(env, envp))
		return (3);
	result = here_doc_line(cmd, env);
	free_tab(env->envp);
	return (result);
}
