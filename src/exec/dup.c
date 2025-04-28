/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:52:59 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/04/25 14:23:26 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	dup_first(t_cmd *cmd, t_cmd *cmd_origin, t_pipe *pipe_fd, t_env *env)
{
	if (cmd->fd_out)
		dup_fd_out(cmd, cmd_origin, env, pipe_fd);
	else if (cmd->nb_cmd > 1)
		if (dup2(pipe_fd->old[1], STDOUT_FILENO) == -1)
			free_cmd_env_pipe(cmd_origin, env, pipe_fd);
	if (cmd->fd_in && !cmd->limiter)
		dup_fd_in(cmd, cmd_origin, env, pipe_fd);
	else if (cmd->limiter)
		dup_heredoc(cmd, cmd_origin, env, pipe_fd);
	close_pipe_fd(pipe_fd->old);
}

void	dup_middle(t_cmd *cmd, t_cmd *cmd_origin, t_pipe *pipe_fd, t_env *env)
{
	if (cmd->fd_in || !cmd->limiter)
		dup_fd_out(cmd, cmd_origin, env, pipe_fd);
	else if (cmd->limiter)
		dup_heredoc(cmd, cmd_origin, env, pipe_fd);
	else if (dup2(pipe_fd->old[0], STDIN_FILENO) == -1)
		free_cmd_env_pipe(cmd_origin, env, pipe_fd);
	if (cmd->fd_out)
		dup_fd_out(cmd, cmd_origin, env, pipe_fd);
	else if (dup2(pipe_fd->new[1], STDOUT_FILENO) == -1)
		free_cmd_env_pipe(cmd_origin, env, pipe_fd);
	close_pipe_fd(pipe_fd->old);
	close_pipe_fd(pipe_fd->new);
}

void	dup_last(t_cmd *cmd, t_cmd *cmd_origin, t_pipe *pipe_fd, t_env *env)
{
	if (cmd->fd_in && !cmd->limiter)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			free_cmd_env_pipe(cmd_origin, env, pipe_fd);
		close(cmd->fd_in);
	}
	else if (cmd->limiter)
		dup_heredoc(cmd, cmd_origin, env, pipe_fd);
	else
	{
		if (dup2(pipe_fd->old[0], STDIN_FILENO) == -1)
			free_cmd_env_pipe(cmd_origin, env, pipe_fd);
	}
	if (cmd->fd_out)
		dup_fd_out(cmd, cmd_origin, env, pipe_fd);
	close_pipe_fd(pipe_fd->old);
}
