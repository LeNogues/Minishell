NAME=minishell
LIBFTNAME=libft.a
CC=cc
CFLAGS=-Wall -Werror -Wextra -Ilibft
LIBFLAGS= -lft -Llibft
LIBFTDIR = ./libft

SRC=    src/main.c \
		src/built_in1.c \
		src/built_in2.c \
		src/built_in_utils1.c \
		src/built_in_utils2.c

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
