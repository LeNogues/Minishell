/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:22:14 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/04/25 15:09:35 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	dup_fd_out(t_cmd *cmd, t_cmd *cmd_origin, t_env *env, t_pipe *pipe_fd)
{
	if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
		free_cmd_env_pipe(cmd_origin, env, pipe_fd);
	close(cmd->fd_out);
}

void	dup_fd_in(t_cmd *cmd, t_cmd *cmd_origin, t_env *env, t_pipe *pipe_fd)
{
	if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
		free_cmd_env_pipe(cmd_origin, env, pipe_fd);
	close(cmd->fd_in);
}

void	dup_heredoc(t_cmd *cmd_origin, t_env *env, t_pipe *pipe_fd)
{
	if (dup2(pipe_fd->heredoc[0], STDIN_FILENO) == -1)
		free_cmd_env_pipe(cmd_origin, env, pipe_fd);
	close_pipe_fd(pipe_fd->heredoc);
}
