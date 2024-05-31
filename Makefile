CC=cc
CFLAGS= -Wall -Wextra -Werror
SRC= philo.c utils.c
OBJ=$(SRC:%.c=%.o)
NAME=philo

$(NAME): $(SRC) philo.h
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

all: $(NAME)

re: fclean all