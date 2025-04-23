/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:59:14 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/04/23 10:47:12 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

char	*ft_write_mini_path(char *mini_path, char *dir, char *command)
{
	const int	size = ft_strlen(dir) + ft_strlen(command) + 2;
	int			i;
	int			j;

	mini_path = malloc(sizeof(char) * size);
	if (!mini_path)
		return (0);
	j = 0;
	i = 0;
	while (dir[j])
		mini_path[i++] = dir[j++];
	mini_path[i++] = '/';
	j = 0;
	while (command[j])
		mini_path[i++] = command[j++];
	mini_path[i] = 0;
	return (mini_path);
}

int	find_executable(char *command, char **full_path)
{
	char	*path;
	char	*dir;

	path = ft_strdup(*full_path);
	if (!path)
		return (-1);
	dir = ft_strtok(path, ':');
	while (dir != NULL)
	{
		free(*full_path);
		*full_path = ft_write_mini_path(*full_path, dir, command);
		if (access(*full_path, X_OK) == 0)
			return (free(path), 0);
		dir = ft_strtok(NULL, ':');
	}
	free(*full_path);
	free(path);
	return (-1);
}

char	*verif_arg(t_cmd *cmd, t_cmd *cmd_origin, t_pipe *pipe_fd, t_env *env)
{
	char	*full_path;

	if (!cmd->cmd)
		return (0);
	if (!cmd->cmd[0])
		exit (EXIT_FAILURE);
	if (access(cmd->cmd[0], X_OK) == 0)
		return (ft_strdup(cmd->cmd[0]));
	full_path = get_path(env);
	if (!full_path)
		free_cmd_env_pipe(cmd_origin, env, pipe_fd);
	if (cmd->cmd[0] == 0)
		return (full_path);
	else if (find_executable(cmd->cmd[0], &full_path) == -1)
	{
		write(2, "Command not found\n", 19);
		full_path = ft_strdup("not found");
		if (!full_path)
			return (0);
	}
	return (full_path);
}
