/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:45:04 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/04/18 16:20:58 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	free_cmd(t_cmd *cmd)
{
	t_cmd *tmp;

	
	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->cmd)
			free_tab(cmd->cmd);
		if (cmd->name_in)
			free(cmd->name_in);
		if (cmd->name_out)
			free(cmd->name_out);
		if (cmd->limiter)
			free(cmd->limiter);
		if (cmd->full_path)
			free(cmd->full_path);
		free(cmd);
		cmd = tmp;
	}
}

void	free_path_exec(char *full_path, char **executable)
{
	int	i;

	free(full_path);
	i = 0;
	while (executable[i])
	{
		free(executable[i]);
		i++;
	}
	free(executable);
}
