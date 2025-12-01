NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a
SRC_DIR = src
OBJ_DIR = obj
SRCS = main.c
OBJS = $(OBJ_DIR)/$(SRC:.c=.o)

all: $(NAME)

$(LIBFT_A)
	make -C $(LIBFT_DIR)

$(NAME): $(LIBFT_A) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -I$(LIBFT_DIR) -o $(NAME)
%.o: %.c
	$$(CC) -I$(LIBFT_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re