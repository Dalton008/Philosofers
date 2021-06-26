NAME = philo

HEADER = includes/philo.h

LIST = philo.c utils.c init.c actions.c free.c

FLAGS = -Wall -Wextra -Werror

OBJ = $(LIST:.c=.o)

.PHONY : all clean fclean re

all : $(NAME)

%.o : %.c $(HEADER)
	gcc $(FLAGS) -I $(HEADER) -c $< -o $@

${NAME} : $(OBJ) $(HEADER)
	gcc $(FLAGS) $(OBJ) -o $(NAME)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all