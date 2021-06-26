NAME = philo_bonus

HEADER = includes/philo_bonus.h

LIST = actions.c init.c philo_bonus.c utils.c kill.c

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