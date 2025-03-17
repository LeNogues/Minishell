/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   built_in1.c                                          ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/03/06 11:12:07 by seb                  │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/17 17:54:27 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

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

int	ft_cd(char **cmd, t_env *env)
{
	char		*path;
	const int	size_tab = ft_tablen(cmd);

	if (size_tab == 1)
	{
		path = ft_strdup(get_home(env));
		if (!path)
			return (write(1, "HOME not set\n", 13), free(path), 0);
	}
	else if (size_tab > 2)
		return (perror("too many arguments"), 0);
	else
		path = ft_strdup(cmd[1]);
	if (chdir(path) == -1)
		return (perror(path), 0);
	change_old_pwd(env);
	change_pwd(env, path);
	return (1);
}

int	ft_echo(t_cmd cmd)
{
	int	i;
	int	newline;

	newline = 1;
	i = 1;
	if (!cmd.cmd)
		return (0);
	i = check_flags(cmd);
	if (i != 1)
		newline = 0;
	while (cmd.cmd[i])
	{
		write(1, cmd.cmd[i], strlen(cmd.cmd[i]));
		if (cmd.cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	i = 0;
	return (1);
}

static void	choice_of_builtin(t_cmd cmd, t_env *env)
{
	if (ft_strncmp(cmd.cmd[0], "cd", 3) == 0)
		ft_cd(cmd.cmd, env);
	else if (ft_strncmp(cmd.cmd[0], "pwd", 4) == 0)
		ft_pwd(env);
	else if (ft_strncmp(cmd.cmd[0], "echo", 5) == 0)
		ft_echo(cmd);
	else if (ft_strncmp(cmd.cmd[0], "env", 4) == 0)
		ft_env(env);
	else if (ft_strncmp(cmd.cmd[0], "unset", 6) == 0)
		ft_unset(cmd.cmd, env);
}

int	here_doc_line(t_cmd cmd, t_env *env)
{
	char	*line;
	int		result;

	result = 1;
	while (result == 1)
	{
		line = readline("\e[32mMinishell : \e[0m");
		if (!line)
			return (0);
		if (line[0] != 0)
		{
			cmd.cmd = ft_split(line, ' ');
			if (!cmd.cmd)
				return (0);
			free(line);
			if (ft_strncmp(cmd.cmd[0], "exit", 5) == 0)
				ft_exit(cmd.cmd, env);
			else
				choice_of_builtin(cmd, env);
			free_tab(cmd.cmd);
		}
	}
	return (result);
}
