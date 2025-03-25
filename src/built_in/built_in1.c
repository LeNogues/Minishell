/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:12:07 by seb               #+#    #+#             */
/*   Updated: 2025/03/25 11:33:47 by sle-nogu         ###   ########.fr       */
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
	else if (ft_strncmp(cmd.cmd[0], "exit", 5) == 0)
		ft_exit(cmd.cmd, env);
	exit(0);
}

void	here_doc_line(t_cmd cmd, t_env *env)
{
	char	*line;
	int id;

	while (1)
	{
		line = readline("\001\e[32m\002Minishell : \001\e[0m\002");
		if (!line)
			return ;
		if (line[0] != 0)
		{
			add_history(line);
			cmd.cmd = ft_split(line, ' ');
			if (!cmd.cmd)
				return ;
			free(line);
			id = fork();
			if (id == 0)
				choice_of_builtin(cmd, env);
			else
			{
				wait(0);
				if (ft_strncmp(cmd.cmd[0], "exit", 5) == 0)
					ft_exit(cmd.cmd, env);
				free_tab(cmd.cmd);
			}
		}
	}
}
