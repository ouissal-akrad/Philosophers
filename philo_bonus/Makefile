NAME = philo_bonus

CFLAGS = -Wall -Wextra -Werror

SRC = 	main.c\
		libft.c\
		cycle.c\
		lst.c\
		philo_bonus_utils.c\

OBJ = $(SRC:.c=.o)

INCLUDES = philo_bonus.h

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
