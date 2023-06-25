NAME = gnl.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS =
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):$(OBJS)
	ar rcs $(NAME) $(OBJS)

.c.o: $(OBJS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean:
	$(RM) $(NAME)

re: fclean all