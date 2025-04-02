NAME=minishell
LIBFTNAME=libft.a
CC=cc
CFLAGS=-Wall -Werror -Wextra -Ilibft -g3
LIBFLAGS= -lft -Llibft
LIBFTDIR = ./libft

SRC=    src/main.c \
		src/built_in/built_in1.c \
		src/built_in/ft_getenv.c \
		src/built_in/ft_export.c \
		src/built_in/ft_export_utils.c \
		src/built_in/ft_cd.c \
		src/built_in/ft_cd_utils.c \
		src/built_in/ft_echo.c \
		src/built_in/ft_env.c \
		src/built_in/ft_exit.c \
		src/built_in/ft_pwd.c \
		src/built_in/ft_unset.c \
		src/signal/signal.c \
		src/exec/exec.c \
		src/exec/exec_loop.c \
		src/exec/parsing.c \
		src/exec/path.c \
		src/utils/free.c

OBJ_DIR=obj
OBJS=$(SRC:%.c=$(OBJ_DIR)/%.o)

# Create necessary directories for .o files
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@make -C $(LIBFTDIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFLAGS) -lreadline

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)
	@cd $(LIBFTDIR) && make clean

fclean: clean
	@rm -f $(NAME)
	@cd $(LIBFTDIR) && make fclean

re: fclean all

all: $(NAME)

default: all

.PHONY: all re clean fclean