/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:04:43 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/04/25 15:14:11 by sle-nogu         ###   ########.fr       */
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

int	loop_on_middle(t_cmd *cmd, t_env *env, t_pipe *pipe_fd, t_cmd *cmd_origin)
{
	int	i;

	i = 0;
	while (i < cmd->nb_cmd - 2)
	{
		if (pipe(pipe_fd->new) == -1)
			return (-3);
		if (!handle_cmd(cmd, env, pipe_fd, cmd_origin))
			return (0);
		pipecpy(pipe_fd->new, pipe_fd->old);
		cmd = cmd->next;
		i++;
	}
	return (1);
}
