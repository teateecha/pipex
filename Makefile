NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR)

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a
SRC_DIR = src
OBJ_DIR = obj

vpath %.c $(foreach dir, $(SRC_DIR), $(dir):)
SRCS = main.c helper.c

#OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))
OBJS = $(OBJ_DIR)/$(SRCS:.c=.o)

all: $(NAME)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT_A) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME)

#build only if OBJ_DIR exists
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -I$(LIBFT_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
