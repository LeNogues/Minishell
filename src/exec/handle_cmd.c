/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:37:22 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/04/23 12:05:21 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	handle_cmd1_2(t_cmd *cmd, t_env *env, t_pipe *pipe_fd, t_cmd *cmd_origin,
		int pos)
{
	int	id;

	id = fork();
	if (id == 0)
	{
		open_fd(cmd, cmd_origin, pipe_fd, env);
		if (pos == 1)
			dup_first(cmd, pipe_fd);
		if (pos == 2)
			dup_last(cmd, pipe_fd);
		if (choice_of_builtin(cmd, env, cmd_origin, pipe_fd) == 0)
			execute(cmd, env, pipe_fd, cmd_origin);
		else
			free_cmd_env_pipe(cmd_origin, env, pipe_fd);
	}
	if (cmd->nb_cmd == 1)
		close_pipe_fd(pipe_fd->old);
	return (1);
}
