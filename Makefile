# COLORS
RED		=	\033[91;1m
GREEN	=	\033[92;1m
YELLOW	=	\033[93;1m
BLUE	=	\033[94;1m
PINK	=	\033[95;1m
CLEAR	=	\033[0m

NAME =philo

CC = gcc
CFLAGS =-Wall -Werror -Wextra -fsanitize=address -g3 -pthread
# CFLAGS =-Wall -Werror -Wextra -g3 -pthread

SRC =	main.c \

OBJ_DIR = obj/
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(PINK)Compiling the pipex.$(CLEAR)"
#	$(CC) $(OBJ) -o $(NAME) -g3 -pthread
	$(CC) $(OBJ) -o $(NAME) -fsanitize=address -g3 -pthread
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