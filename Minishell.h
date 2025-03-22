/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:03:48 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/03/22 15:09:15 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1

# endif

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
# include "./libft.h"

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
int						ft_pwd(t_env *env);
int						ft_cd(char **path, t_env *env);
int						ft_echo(t_cmd cmd);
int						here_doc_line(t_cmd cmd, t_env *envp);
///////////////////////////////////////////////////////////////////////////////

// built_in2.c
void					ft_exit(char **cmd, t_env *env);
void					ft_env(t_env *env);
void					ft_unset(char **cmd, t_env *env);
int						is_in_tab(char *str, char **cmd);
///////////////////////////////////////////////////////////////////////////////

// main.c
int						main(int argc, char **argv, char **envp);
int						set_environment(t_env *env, char **envp);
///////////////////////////////////////////////////////////////////////////////

// built_in_utils1.c
void					change_pwd(t_env *env, char *path);
void					change_old_pwd(t_env *env);
char					*get_home(t_env *env);
int						check_flags(t_cmd cmd);
char					*ft_getenv(char *value_name, t_env *env);
///////////////////////////////////////////////////////////////////////////////

// built_in_utils2.c
char					*create_new_path(t_env *env, char *path);
long					ft_atol(const char *str, long *result);
///////////////////////////////////////////////////////////////////////////////

#endif
