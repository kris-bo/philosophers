
NAME	= philo

SRC		= main.c ft_atoi.c eat.c init.c death.c utils.c access.c
OBJ		= $(SRC:.c=.o)

CC		= clang
CFLAGS	= -Wall -Wextra -Werror -pthread # -fsanitize=thread

all : $(NAME)

%.o : %.c
	$(CC) -c $< -o $@

$(NAME) : $(OBJ) philo.h Makefile
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm $(NAME)

re : fclean all

.PHONY : all clean fclean re