/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:45:04 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/04/25 10:56:12 by sle-nogu         ###   ########.fr       */
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
		if (cmd->name_in)
			free_tab(cmd->name_in);
		if (cmd->name_out)
			free_tab(cmd->name_out);
		if (cmd->limiter)
			free_tab(cmd->limiter);
		if (cmd->append)
			free(cmd->append);
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
	if (cmd->name_in)
		free_tab(cmd->name_in);
	if (cmd->name_out)
		free_tab(cmd->name_out);
	if (cmd->limiter)
		free(cmd->limiter);
	if (cmd->full_path)
		free(cmd->full_path);
}

void	free_cmd_env_pipe(t_cmd *cmd_origin, t_env *env, t_pipe *pipe_fd)
{
	free_all_cmd(cmd_origin);
	free_tab(env->envp);
	free(pipe_fd);
	free(env);
	exit(EXIT_FAILURE);
}
