CC=cc
CFLAGS= -Wall -Wextra -Werror
SRC= philo.c locks.c utils.c
NAME=philo

$(NAME): $(SRC) philo.h
	$(CC) $(CFLAGS) -o $(NAME) $(SRC)

clean:

fclean: clean
	rm -f $(NAME)

all: $(NAME)

re: fclean all