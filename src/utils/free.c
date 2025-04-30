/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:45:04 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/04/29 16:23:00 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	free_all_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->cmd)
			free_tab(cmd->cmd);
		if (cmd->name)
			free_tab(cmd->name);
		if (cmd->in_or_out)
			free(cmd->in_or_out);
		if (cmd->full_path)
			free(cmd->full_path);
		free(cmd);
		cmd = tmp;
	}
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd->cmd)
		free_tab(cmd->cmd);
	if (cmd->name)
		free_tab(cmd->name);
	if (cmd->in_or_out)
		free(cmd->in_or_out);
	if (cmd->full_path)
		free(cmd->full_path);
	free(cmd);
}

void	free_cmd_env_pipe(t_cmd *cmd_origin, t_env *env, t_pipe *pipe_fd)
{
	free_all_cmd(cmd_origin);
	free_tab(env->envp);
	free(pipe_fd);
	free(env);
	exit(EXIT_FAILURE);
}
