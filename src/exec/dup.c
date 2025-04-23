/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:52:59 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/04/23 11:53:29 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	dup_first(t_cmd *cmd, t_pipe *pipe_fd)
{
	if (cmd->fd_out)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	else if (cmd->nb_cmd > 1)
	{
		dup2(pipe_fd->old[1], STDOUT_FILENO);
	}
	if (cmd->fd_in)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	close_pipe_fd(pipe_fd->old);
}

void	dup_middle(t_cmd *cmd, t_pipe *pipe_fd)
{
	if (cmd->fd_in)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	else
		dup2(pipe_fd->old[0], STDIN_FILENO);
	if (cmd->fd_out)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	else
	{
		dup2(pipe_fd->new[1], STDOUT_FILENO);
	}
	close_pipe_fd(pipe_fd->old);
	close_pipe_fd(pipe_fd->new);
}

void	dup_last(t_cmd *cmd, t_pipe *pipe_fd)
{
	if (cmd->fd_in)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	else
	{
		dup2(pipe_fd->old[0], STDIN_FILENO);
	}
	if (cmd->fd_out)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	close_pipe_fd(pipe_fd->old);
}
