/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:03:48 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/04/02 17:40:49 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1

# endif

# include "libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

typedef struct s_args
{
	char			*file;
	char			*full_path;
	char			**executable;
}					t_args;

typedef struct s_cmd
{
	char			**cmd;
	char			**limiter;
	char			*name_in;
	char			*name_out;
	int				fd_in;
	int				pipe;
	int				fd_out;
	int				append;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_pipe
{
	int				old[2];
	int				new[2];
}					t_pipe;

typedef struct s_env
{
	char			**envp;
	int				sz;
}					t_env;

// built_in1.c
void				hub(t_env *envp);
///////////////////////////////////////////////////////////////////////////////

// ft_pwd.c
int					ft_pwd(t_env *env);
///////////////////////////////////////////////////////////////////////////////

// ft_cd.c
int					ft_cd(char **path, t_env *env);
///////////////////////////////////////////////////////////////////////////////

// ft_cd_utils.c
int					cd_home(t_env *env, char **path);
///////////////////////////////////////////////////////////////////////////////

// ft_echo.c
int					ft_echo(t_cmd cmd);
///////////////////////////////////////////////////////////////////////////////

// ft_exit.c
void				ft_exit(t_cmd *cmd, t_env *env);
///////////////////////////////////////////////////////////////////////////////

// ft_env.c
void				ft_env(t_env *env);
///////////////////////////////////////////////////////////////////////////////

// ft_unset.c
void				ft_unset(char **cmd, t_env *env);
///////////////////////////////////////////////////////////////////////////////

// ft_export.c
void				ft_export(char **cmd, t_env *env);
///////////////////////////////////////////////////////////////////////////////

// ft_export_utils.c
int					is_valid(char *str);
///////////////////////////////////////////////////////////////////////////////

// main.c
int					main(int argc, char **argv, char **envp);
int					set_environment(t_env *env, char **envp);
///////////////////////////////////////////////////////////////////////////////

// ft_getenv.c
char				*ft_getenv(char *value_name, t_env *env);
///////////////////////////////////////////////////////////////////////////////

// signal.c
void				handle_signal(void);
///////////////////////////////////////////////////////////////////////////////

// exec.c
int					exec(t_cmd cmd, t_env *env);
void				execute_middle(t_cmd *cmd, char *full_path, t_env *env,
						t_pipe pipe_fd);
///////////////////////////////////////////////////////////////////////////////

// exec_loop.c
int					exec_loop(t_cmd *cmd, t_env *env, t_pipe *pipe_fd);
///////////////////////////////////////////////////////////////////////////////

// parsing.c
char				*verif_arg(char **executable, t_env *env);
///////////////////////////////////////////////////////////////////////////////

// path.c
char				*get_path(t_env *env);
///////////////////////////////////////////////////////////////////////////////

// free.c
void				free_path_exec(char *full_path, char **executable);
void				free_cmd(t_cmd *cmd);
///////////////////////////////////////////////////////////////////////////////

#endif
