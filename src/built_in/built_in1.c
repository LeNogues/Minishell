/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:12:07 by seb               #+#    #+#             */
/*   Updated: 2025/05/06 20:42:32 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	choice_of_builtin(t_cmd *cmd, t_env *env, t_cmd *cmd_origin,
		t_pipe *pipe_fd)
{
	if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
		return (ft_cd(cmd->cmd, env), 1);
	else if (ft_strncmp(cmd->cmd[0], "pwd", 4) == 0)
		return (ft_pwd(env), 1);
	else if (ft_strncmp(cmd->cmd[0], "echo", 5) == 0)
		return (ft_echo(cmd), 1);
	else if (ft_strncmp(cmd->cmd[0], "env", 4) == 0)
		return (ft_env(env), 1);
	else if (ft_strncmp(cmd->cmd[0], "unset", 6) == 0)
		return (ft_unset(cmd->cmd, env), 1);
	else if (ft_strncmp(cmd->cmd[0], "export", 7) == 0)
		return (ft_export(cmd->cmd, env), 1);
	if (ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
		ft_exit(cmd_origin, env, pipe_fd);
	return (0);
}

void	hub(t_info *info)
{
	char	*line;

	while (1)
	{
		g_state_signal = 1;
		line = readline("\001\e[32m\002Minishell : \001\e[0m\002");
		if (!line)
			return ;
		if (line[0] != 0)
		{
			add_history(line);
			info->cmd = merge(info, line);
			if (info->cmd)
			{
				info->cmd_origin = info->cmd;
				free(line);
				exec(info);
				free_all_cmd(info->cmd_origin);
			}
		}
	}
}
