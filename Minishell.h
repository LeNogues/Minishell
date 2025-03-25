/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:03:48 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/03/24 18:03:15 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1

# endif

# include "libft.h"
# include <dirent.h>
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

typedef struct s_env	t_env;

typedef struct s_args
{
	char				*file;
	char				*full_path;
	char				**executable;
}						t_args;

typedef struct s_cmd
{
	char				**cmd;
	char				**limiter;
	char				*name_in;
	char				*name_out;
	int					fd_in;
	int					fd_out;
	int					append;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_pipe
{
	int					old[2];
	int					new[2];
}						t_pipe;

struct					s_env
{
	char				**envp;
	int					sz;
};

// built_in1.c

void					here_doc_line(t_cmd cmd, t_env *envp);
///////////////////////////////////////////////////////////////////////////////

// ft_pwd.c
int						ft_pwd(t_env *env);
///////////////////////////////////////////////////////////////////////////////

// ft_cd.c
int						ft_cd(char **path, t_env *env);
///////////////////////////////////////////////////////////////////////////////

// ft_cd_utils.c
int						cd_home(t_env *env, char **path);
///////////////////////////////////////////////////////////////////////////////

// ft_echo.c
int						ft_echo(t_cmd cmd);
///////////////////////////////////////////////////////////////////////////////

// ft_exit.c
void					ft_exit(char **cmd, t_env *env);
///////////////////////////////////////////////////////////////////////////////

// ft_env.c
void					ft_env(t_env *env);
///////////////////////////////////////////////////////////////////////////////

// ft_unset.c
void					ft_unset(char **cmd, t_env *env);
///////////////////////////////////////////////////////////////////////////////

// ft_export.c
void					ft_export(char **cmd, t_env *env);
///////////////////////////////////////////////////////////////////////////////

// ft_export_utils.c
int						is_valid(char *str);
///////////////////////////////////////////////////////////////////////////////

// main.c
int						main(int argc, char **argv, char **envp);
int						set_environment(t_env *env, char **envp);
///////////////////////////////////////////////////////////////////////////////

// ft_getenv.c
char					*ft_getenv(char *value_name, t_env *env);
///////////////////////////////////////////////////////////////////////////////

//signal.c
void    handle_signal(void);
///////////////////////////////////////////////////////////////////////////////


#endif
