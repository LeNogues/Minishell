/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:04:43 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/04/21 15:43:01 by sle-nogu         ###   ########.fr       */
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
	int		id;
	int 	i;

	i = 0;
	while (i < cmd->nb_cmd - 2)
	{
		if (pipe(pipe_fd->new) == -1)
			return (-3);
		id = fork();
		if(id == 0)
		{
			open_fd(cmd);
			dup_middle(cmd, pipe_fd);
			if(choice_of_builtin(cmd, env, cmd_origin, pipe_fd) == 0)
			{
				cmd->full_path = verif_arg(cmd->cmd, env);
				if (!cmd->full_path)
					return (0);
				if(execute(cmd, *env, pipe_fd) == -1)
				{
					free(env);
					exit(EXIT_FAILURE);
				}
			}	
		}
		pipecpy(pipe_fd->new, pipe_fd->old);
		cmd = cmd->next;
		i++;
		if(i >= cmd->nb_cmd - 2)
		{
			pipe_fd->new[0] = -1;
			pipe_fd->new[1] = -1;
		}
	}
	return (0);
}
