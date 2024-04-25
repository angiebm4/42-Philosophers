# COLORS
RED		=	\033[91;1m
GREEN	=	\033[92;1m
YELLOW	=	\033[93;1m
BLUE	=	\033[94;1m
PINK	=	\033[95;1m
CLEAR	=	\033[0m

NAME =philo

CC = gcc
#CFLAGS =-Wall -Werror -Wextra -fsanitize=thread -g3 -pthread
#CFLAGS =-Wall -Werror -Wextra -fsanitize=address -g3 -pthread
CFLAGS =-Wall -Werror -Wextra -pthread -O3

SRC =	main.c \
		init.c \
		philo_utils.c \
		start.c \
		rutine.c \
		doctor.c \
		rutine_habits.c \
		time.c 

OBJ_DIR = obj/
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(PINK)Compiling the philo.$(CLEAR)"
	$(CC) $(OBJ) -o $(NAME) -pthread -O3
#	$(CC) $(OBJ) -o $(NAME) -fsanitize=thread -g3 -pthread
#	$(CC) $(OBJ) -o $(NAME) -fsanitize=address -g3 -pthread
	@echo "$(GREEN)[OK]\n$(CLEAR)$(GREEN)Success!$(CLEAR)\n"

bonus: $(NAME)

$(OBJ_DIR)%.o: src/%.c
	@echo "$(PINK)Compiling Object.$(CLEAR)"
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "\n"

clean:
	@echo "$(PINK)Removing compiled files.$(CLEAR)"
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)Object files removed correctly\n$(CLEAR)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(GREEN)Exec. files removed correctly\nSuccess!\n$(CLEAR)"

re: fclean all
.PHONY: clean fclean re all


t1: all
	./philo 5 800 200 200

t2: all
	./philo 5 800 200 200 7
# se me mueren
t3: all
	./philo 4 410 200 200

t4: all
	./philo 4 310 200 100

t5: all
	./philo 1 310 200 100 

t6: all
	./philo 4 310 200 100 0

t7: all
	./philo 30 800 200 200