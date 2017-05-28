NAME = factrace

SRC_NAME = 	main.c
OBJ_NAME = $(SRC_NAME:.c=.o)
SRC_PATH =	src/
OBJ_PATH =  obj/
CC = clang

W_FLAGS = -Werror -Wall -Wextra
I_FLAGS = -Iincludes

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
LIB = -Llib -lgmp -Wl,-no_pie

all: $(NAME)

$(NAME):
	@echo "------------all-------------"
		@echo "\033[0;31m$(NAME)  :\033[0m\c"
			@$(CC) $(W_FLAGS) $(I_FLAGS) -c $(SRC)
			@mkdir $(OBJ_PATH) 2> /dev/null || true
			@mv $(OBJ_NAME) $(OBJ_PATH)
			@$(CC) $(W_FLAGS) -o $(NAME) $(OBJ) $(LIB)
		@echo "\033[0;32m    OK\033[0m"
	@echo "----------------------------\n"
clean:
	@echo "-----------clean------------"
		@echo "\033[0;31m$(NAME)  :\033[0m\c"
			@rm -rf $(OBJ)
			@rmdir $(OBJ_PATH) 2> /dev/null || true
		@echo "\033[0;32m    OK\033[0m"
	@echo "----------------------------"

fclean: clean
	@echo "-----------fclean-----------"
		@echo "\033[0;31m$(NAME)  :\033[0m\c"
			@rm -rf $(NAME)
		@echo "\033[0;32m    OK\033[0m"
	@echo "----------------------------"

re: fclean all
