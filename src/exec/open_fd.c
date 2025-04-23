/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:27:23 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/04/23 11:30:34 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	open_in(t_cmd *cmd, t_cmd *cmd_origin, t_pipe *pipe_fd, t_env *env)
{
	cmd->fd_in = open(cmd->name_in, O_RDONLY);
	if (cmd->fd_in == -1)
		free_cmd_env_pipe(cmd_origin, env, pipe_fd);
}

void	open_out(t_cmd *cmd, t_cmd *cmd_origin, t_pipe *pipe_fd, t_env *env)
{
	cmd->fd_out = open(cmd->name_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd_out == -1)
		free_cmd_env_pipe(cmd_origin, env, pipe_fd);
}

void	open_out_append(t_cmd *cmd, t_cmd *cmd_origin, t_pipe *pipe_fd,
		t_env *env)
{
	cmd->fd_out = open(cmd->name_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->fd_out == -1)
		free_cmd_env_pipe(cmd_origin, env, pipe_fd);
}

int	open_fd(t_cmd *cmd, t_cmd *cmd_origin, t_pipe *pipe_fd, t_env *env)
{
	if (cmd->name_in)
		open_in(cmd, cmd_origin, pipe_fd, env);
	if (cmd->name_out && cmd->append == 0)
		open_out(cmd, cmd_origin, pipe_fd, env);
	if (cmd->name_out && cmd->append == 1)
		open_out_append(cmd, cmd_origin, pipe_fd, env);
	return (0);
}
