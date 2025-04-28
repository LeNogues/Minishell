/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:28:19 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/04/27 16:13:28 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	verif_file(t_cmd *cmd, t_cmd *cmd_origin, t_env *env, t_pipe *pipe_fd)
{
	int	fd;
	int	i;
	int result;

	if (!cmd->name[i])
		return (1);
	i = 0;
	result = 1;
	while (cmd->name[i])
	{
		if (cmd->in_or_out[i] == INPUT)
			result = open_in(cmd, cmd->name[i]);
		else if (cmd->in_or_out[i] == OUTPUT_APPEND || cmd->in_or_out[i] == OUTPUT_TRUNC)
			result = open_out(cmd, cmd->name[i], cmd->in_or_out[i]);
		else if (cmd->in_or_out[i] == HEREDOC)
			result = open_heredoc(cmd, cmd->name[i], pipe_fd);
		if (fd == -1)
		{
			write(2, "could not execute file\n", 24);
			return (-1);
		}
		i++;
	}
	if (!result)
		free_cmd_env_pipe(cmd_origin, env, pipe_fd);
	return (1);
}
