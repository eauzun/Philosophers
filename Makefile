NAME = philosophers

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -f

SRCS = philosophers.c \
       init.c \
       utils.c \
       routine.c \
       monitor.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re