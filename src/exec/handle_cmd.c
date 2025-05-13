/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:37:22 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/05/11 16:18:05 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	dup_no_fd(t_cmd *cmd, t_pipe *pipe_fd)
{
	if (cmd->pos == 1)
		dup_first(cmd, pipe_fd);
	if (cmd->pos == 2)
		dup_middle(cmd, pipe_fd);
	if (cmd->pos == 3)
		dup_last(cmd, pipe_fd);
}

static void	ctrl_back(int sig)
{
	(void)sig;
	if (g_state_signal != 1)
	{
		write(1, "Quit (core dumped)\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		if (g_state_signal == 3)
			g_state_signal = 4;
	}
}

int	handle_cmd(t_info *info, t_pipe *pipe_fd)
{
	int	id;
	int	built;

	built = 0;
	id = -1;
	if (info->cmd->nb_cmd == 1)
		built = choice_of_builtin(info->cmd, info->env,
				info->cmd_origin, pipe_fd);
	if (built == 0)
		id = fork();
	if (id == 0)
	{
		signal(SIGQUIT, ctrl_back);
		if (!verif_file(info->cmd, info->cmd_origin, info->env, pipe_fd))
			free_cmd_env_pipe(info->cmd_origin, info->env, pipe_fd);
		dup_no_fd(info->cmd, pipe_fd);
		if (!choice_of_builtin(info->cmd, info->env, info->cmd_origin, pipe_fd))
			execute(info->cmd, info->env, pipe_fd, info->cmd_origin);
		else
			free_cmd_env_pipe(info->cmd_origin, info->env, pipe_fd);
	}
	info->last_pid = id;
	g_state_signal = 2;
	if (info->cmd->nb_cmd == 1)
		close_pipe_fd(pipe_fd->old);
	return (1);
}
