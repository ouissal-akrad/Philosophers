NAME = philo

CFLAGS = -Wall -Wextra -Werror

SRC = 	main.c\
		libft.c\

OBJ = $(SRC:.c=.o)

INCLUDES = philosophers.h

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
