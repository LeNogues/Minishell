/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:28:19 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/05/06 21:21:42 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	verif_file(t_cmd *cmd, t_cmd *cmd_origin, t_env *env, t_pipe *pipe_fd)
{
	int	i;
	int	result;

	if (!cmd->name)
		return (1);
	i = 0;
	while (cmd->name[i])
	{
		if (cmd->in_or_out[i] == INPUT)
			result = open_in(cmd, cmd->name[i]);
		else if (cmd->in_or_out[i] == OUTPUT_APPEND
			|| cmd->in_or_out[i] == OUTPUT_TRUNC)
			result = open_out(cmd, cmd->name[i], cmd->in_or_out[i]);
		else
			result = open_heredoc(cmd, cmd->name[i], pipe_fd);
		if (!result)
		{
			write(2, "could not execute file\n", 24);
			close_pipe_fd(pipe_fd->old);
			free_cmd_env_pipe(cmd_origin, env, pipe_fd);
			return (0);
		}
		i++;
	}
	return (1);
}
