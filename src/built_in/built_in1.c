/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:12:07 by seb               #+#    #+#             */
/*   Updated: 2025/04/02 17:40:35 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

static void	choice_of_builtin(t_cmd cmd, t_env *env)
{
	if (ft_strncmp(cmd.cmd[0], "cd", 3) == 0)
		ft_cd(cmd.cmd, env);
	else if (ft_strncmp(cmd.cmd[0], "pwd", 4) == 0)
		ft_pwd(env);
	else if (ft_strncmp(cmd.cmd[0], "echo", 5) == 0)
		ft_echo(cmd);
	else if (ft_strncmp(cmd.cmd[0], "env", 4) == 0)
		ft_env(env);
	else if (ft_strncmp(cmd.cmd[0], "unset", 6) == 0)
		ft_unset(cmd.cmd, env);
	else if (ft_strncmp(cmd.cmd[0], "export", 7) == 0)
		ft_export(cmd.cmd, env);
	else
		exec(cmd, env);
}

t_cmd	*lexer(char *line)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd) * 1);
	cmd->cmd = ft_split(line, ' ');
	cmd->name_in = ft_strdup("test.txt");
	cmd->name_out = ft_strdup("teste.txt");
	cmd->limiter = NULL;
	cmd->append = 0;
	cmd->pipe = 1;
	cmd->fd_in = 0;
	cmd->fd_out = 0;
	cmd->next = NULL;
	return (cmd);
}

void	hub(t_env *env)
{
	t_cmd	*cmd;
	char	*line;

	while (1)
	{
		line = readline("\001\e[32m\002Minishell : \001\e[0m\002");
		if (!line)
			return ;
		if (line[0] != 0)
		{
			add_history(line);
			cmd = lexer(line);
			free(line);
			if (ft_strncmp((*cmd).cmd[0], "exit", 5) == 0)
				ft_exit(cmd, env);
			else
				choice_of_builtin((*cmd), env);
			free_cmd(cmd);
		}
	}
}
