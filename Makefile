NAME = pipex
HEADER = pipex.h
PRINTF = ./printf/libftprintf.a
PRINTF_DIR = ./printf
CC = gcc
INC = -I. -I$(PRINTF_DIR)
FLAGS = -Wall -Wextra -Werror
RM = rm -f


SRC = pipex.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(PRINTF)
	$(CC) $(FLAGS) $(SRC) $(PRINTF) $(INC) -o $(NAME)

$(PRINTF):
	$(MAKE) -C $(PRINTF_DIR)

clean: 
	$(RM) $(NAME)

fclean: clean
	$(MAKE) fclean -C $(PRINTF_DIR)

re: fclean all

bonus: $(NAME)

.PHONY: all clean fclean re bonus 

