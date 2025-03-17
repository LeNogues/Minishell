
NAME=minishell
CC=cc
CFLAGS=-Wall -Werror -Wextra -O0 -g -fsanitize=address

OBJS=$(SRC:.c=.o)

SRC=	main.c \
		mini_libft.c \
		ft_split.c \
		built_in1.c \
		built_in2.c \
		tablen.c \
		clear.c \
		built_in_utils1.c \
		built_in_utils2.c

# Compilation rules
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -lreadline $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

all: $(NAME)

default: all

.PHONY: all re clean fclean
