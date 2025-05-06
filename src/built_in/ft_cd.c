/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:43:35 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/05/06 20:39:30 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

static int	create_env_cd(char *env_to_create, t_env *env)
{
	char	**cmd;

	cmd = ft_split(env_to_create, ' ');
	if (!cmd)
		return (0);
	ft_export(cmd, env);
	free_tab(cmd);
	return (1);
}

static char	*create_new_path(t_env *env, char *path)
{
	char	*cwd;
	char	*temp;

	cwd = ft_getenv("PWD=", env);
	if (!cwd)
		return (perror("ft_getenv"), NULL);
	temp = ft_strjoin(cwd, "/");
	if (!temp)
		return (free(cwd), perror("ft_strjoin"), NULL);
	free(cwd);
	cwd = ft_strjoin(temp, path);
	if (!cwd)
		return (free(temp), free(path), perror("ft_strjoin"), NULL);
	free(path);
	free(temp);
	path = ft_strdup(cwd);
	if (!path)
		return (free(cwd), perror("ft_strdup"), NULL);
	free(cwd);
	return (path);
}

static void	change_pwd(t_env *env, char *path)
{
	char	*new_pwd;
	int		i;

	i = 0;
	if (!env || !env->envp)
		return ;
	while (env->envp[i])
	{
		if (ft_strncmp("PWD=", env->envp[i], 4) == 0)
			break ;
		i++;
	}
	if (path[0] != '/')
		path = create_new_path(env, path);
	if (ft_strncmp(path, "..", 3) == 1)
		new_pwd = get_parent(env);
	else
		new_pwd = ft_strjoin("PWD=", path);
	if (!new_pwd)
		return (perror("ft_strjoin"), free(path));
	free(env->envp[i]);
	free(path);
	env->envp[i] = new_pwd;
}

static void	change_old_pwd(t_env *env)
{
	char	*cwd;
	char	*old_pwd;
	int		i;

	i = 0;
	if (!env || !env->envp)
		return ;
	while (env->envp[i])
	{
		if (ft_strncmp("OLDPWD=", env->envp[i], 7) == 0)
			break ;
		i++;
	}
	if (!env->envp[i])
		if (!create_env_cd("export OLDPWD=", env))
			return ;
	cwd = ft_getenv("PWD=", env);
	if (!cwd)
		return (perror("ft_getenv"));
	old_pwd = ft_strjoin("OLDPWD=", cwd);
	if (!old_pwd)
		return (perror("ft_strjoin"));
	free(env->envp[i]);
	free(cwd);
	env->envp[i] = old_pwd;
}

int	ft_cd(char **cmd, t_env *env)
{
	char		*path;
	const int	size_tab = ft_tablen(cmd);

	path = NULL;
	if (size_tab == 1)
	{
		if (!cd_home(env, &path))
			return (0);
	}
	else if (size_tab > 2)
		return (perror("too many arguments"), 0);
	else
	{
		if (path)
			free(path);
		path = ft_strdup(cmd[1]);
	}
	if (chdir(path) == -1)
		return (perror(path), free(path), 0);
	change_old_pwd(env);
	change_pwd(env, path);
	return (1);
}
