NAME = pipex
SRCS = ft_split.c childer.c pipex.c utils.c
BSRCS = childer_bonus.c ft_split_bonus.c pipex_bonus.c utils_bonus.c get_next_line.c get_next_line_utils.c
CC = cc 
CFLAGS = -Wall -Wextra -Werror
OBJS = $(SRCS:.c=.o)
BOBJS = $(BSRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

bonus : $(BOBJS)

$(BOBJS) : $(BSRCS)
	$(CC) -c $(CFLAGS) $(BSRCS)
	$(CC) $(CFLAGS) $(BSRCS) -o $(NAME)

clean:
	rm -f $(OBJS) $(BOBJS)

fclean:	clean
	rm -f $(NAME)

re:fclean all