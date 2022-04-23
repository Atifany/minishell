# executable
NAME = minishell

# sources
_SRC = core.c utils.c
SRC_DIR = sources
SRC = $(_SRC:%=$(SRC_DIR)/%)
# tmp files
OBJ_DIR = tmp_files
OBJ = $(_SRC:%.c=$(OBJ_DIR)/%.o)
DPS = $(_SRC:%.c=$(OBJ_DIR)/%.d)

# libraries


# Make commands
CC = gcc
C_FLAGS = -O2 -Wall -Wextra -Werror
RM = rm -f

# rules
all: create_dirs compile_libs $(NAME)

create_dirs:
	@mkdir -p tmp_files

compile_libs:
#	

-include $(DPS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(C_FLAGS) -c $< -o $@
	$(CC) -MM $(C_FLAGS) $< > $(OBJ_DIR)/$*.d

$(NAME): $(OBJ)
	$(CC) $(OBJ) -lreadline -o $@

clean:
	$(RM) $(OBJ) $(DPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all re clean compile_libs
