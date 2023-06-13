NAME = philo

CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=thread

SRC = 	main.c\
		libft.c\
		cycle.c\
		lst.c\
		philo_utils.c\

OBJ = $(SRC:.c=.o)

INCLUDES = philo.h

all: $(NAME)

%.o : %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
