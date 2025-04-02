/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:04:43 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/04/02 17:38:49 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	pipecpy(int new_fd[2], int old_fd[2])
{
	close(old_fd[0]);
	close(old_fd[1]);
	old_fd[0] = new_fd[0];
	old_fd[1] = new_fd[1];
}

int	open_fd(t_cmd *cmd, t_pipe *pipe_fd)
{
	(void)pipe_fd;
	if ((*cmd).name_in)
	{
		(*cmd).fd_in = open((*cmd).name_in, O_RDONLY);
		if ((*cmd).fd_in == -1)
			exit(EXIT_FAILURE);
	}
	if ((*cmd).name_out && (*cmd).append == 0)
	{
		(*cmd).fd_out = open((*cmd).name_out, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if ((*cmd).fd_out == -1)
			exit(EXIT_FAILURE);
	}
	if ((*cmd).name_out && (*cmd).append == 1)
	{
		(*cmd).fd_out = open((*cmd).name_out, O_WRONLY | O_CREAT | O_APPEND,
				0644);
		if ((*cmd).fd_out == -1)
			exit(EXIT_FAILURE);
	}
	return (0);
}

int	exec_loop(t_cmd *cmd, t_env *env, t_pipe *pipe_fd)
{
	int		id;
	char	*full_path;

	while (1)
	{
		if (cmd->cmd)
			full_path = verif_arg(cmd->cmd, env);
		if (!full_path)
			return (free_tab((*cmd).cmd), -2);
		id = fork();
		if (id == 0 && cmd->cmd[0] != 0)
		{
			open_fd(cmd, pipe_fd);
			execute_middle(cmd, full_path, env, *pipe_fd);
		}
		wait(0);
		free(full_path);
		// pipecpy(pipe_fd->new, pipe_fd->old);
		if (cmd->next)
			cmd = (*cmd).next;
		else
			break ;
	}
	return (0);
}
