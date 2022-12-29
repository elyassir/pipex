NAME = pipex
SRCS = Mandatory/ft_split.c Mandatory/childer.c Mandatory/pipex.c Mandatory/utils.c
BSRCS = bonus/childer_bonus.c bonus/ft_split_bonus.c bonus/pipex_bonus.c bonus/utils_bonus.c
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