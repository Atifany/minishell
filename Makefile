# executable
NAME = minishell

# sources
_SRC = core.c utils.c commands.c
SRC_DIR = sources
SRC = $(_SRC:%=$(SRC_DIR)/%)
# tmp files
OBJ_DIR = tmp_files
OBJ = $(_SRC:%.c=$(OBJ_DIR)/%.o)
DPS = $(_SRC:%.c=$(OBJ_DIR)/%.d)

# libraries
LIBFT_DIR = libs/libft/
LIBFT = libft.a
LIBS = $(LIBFT:%=$(LIBFT_DIR)%)

# Make commands
CC = gcc
C_FLAGS = -O2 -Wall -Wextra -Werror
RM = rm -f

# rules
all: compile_libs create_dirs compile_libs log_compile_start $(NAME)

compile_libs:
	@printf "\n>> compile libft\n"
	@make -C $(LIBFT_DIR)

create_dirs:
	@mkdir -p tmp_files

compile_libs:
#	

-include $(DPS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(C_FLAGS) -c $< -o $@
	$(CC) -MM $(C_FLAGS) $< > $(OBJ_DIR)/$*.d

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBS) -lreadline -o $@

clean:
	@printf "\n>> clean tmp files\n"
	$(RM) $(OBJ) $(DPS)

fclean: clean
	@printf "\n>> clean executable\n"
	$(RM) $(NAME)

clean_libs:
	@printf "\n>> cleaning libft\n"
	@make -C $(LIBFT_DIR) fclean

re: fclean all

log_compile_start:
	@printf "\n>> compile sources\n"

.PHONY: all re clean compile_libs create_dirs clean_libs log_compile_start
