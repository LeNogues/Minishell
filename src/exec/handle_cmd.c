/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:37:22 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/04/21 16:09:35 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	handle_cmd1_2(t_cmd *cmd, t_env *env, t_pipe *pipe_fd, t_cmd *cmd_origin, int pos)
{
	int		id;

	id = fork();
	if (id == 0)
	{
		open_fd(cmd);
		if(pos == 1)
			dup_first(cmd, pipe_fd);
		if(pos == 2)
			dup_last(cmd, pipe_fd);
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
	if(cmd->nb_cmd == 1)
	{
		close(pipe_fd->old[0]);
		close(pipe_fd->old[1]);
	}
	return (0);
}
