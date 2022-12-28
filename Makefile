NAME = pipex
SRCS = ft_split.c childer.c pipex.c
BSRCS = bonus/childer.c bonus/ft_split.c bonus/pipex.c
CC = cc
CFLAGS = -Wall -Wextra -Werror
OBJS = $(SRCS:.c=.o)
BOBJS = $(BSRCS:.c=.o)

all:$(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

bonus:$(BOBJS)
	$(CC) $(FLAGS) $(BOBJS) -o $(NAME)

clean:
	rm -f $(OBJS) $(BOBJS)

fclean:	clean
	rm -f $(NAME)

re:fclean all