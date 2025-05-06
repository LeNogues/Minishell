/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_origin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:55:52 by seb               #+#    #+#             */
/*   Updated: 2025/05/06 20:56:59 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	init_origin( t_pipe *pipe_fd)
{
	pipe_fd->fd_stdin = STDIN_FILENO;
	pipe_fd->fd_stdout = STDOUT_FILENO;
}

void	restore_origin(t_cmd *cmd_origin, t_env *env, t_pipe *pipe_fd)
{
	if (dup2(pipe_fd->fd_stdin, STDIN_FILENO) == -1)
		free_cmd_env_pipe(cmd_origin, env, pipe_fd);
	if (dup2(pipe_fd->fd_stdout, STDOUT_FILENO) == -1)
		free_cmd_env_pipe(cmd_origin, env, pipe_fd);
}
