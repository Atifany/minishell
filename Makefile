# executable
NAME = minishell

# sources
_SRC =	builtins/commands.c			\
		core/core.c					\
		core/processing.c			\
		envs/environment.c			\
		parse/parse_to_struct.c		\
		parse/parse_utils.c			\
		parse/parse.c				\
		redirects/pipe_in.c			\
		redirects/redirects.c		\
		utils/cat.c					\
		utils/class_methods.c		\
		utils/dictionary.c			\
		utils/get_next_line_utils.c	\
		utils/get_next_line.c		\
		utils/inits.c				\
		utils/utils.c				\
		
SRC_DIR = sources
SRC = $(_SRC:%=$(SRC_DIR)/%)
# tmp files
OBJ_DIR = tmp_files
#_OBJ = $(shell basename $(_SRC))
#OBJ = $(_OBJ:%.c=$(OBJ_DIR)/%.o)
OBJ = $(SRC:%.c=%.o)
#DPS = $(_OBJ:%.c=$(OBJ_DIR)/%.d)
DPS = $(SRC:%.c=%.d)

# libraries
LIBFT_DIR = libs/libft/
LIBFT = libft.a
LIBS = $(LIBFT:%=$(LIBFT_DIR)%)

# Make commands
CC = gcc
C_FLAGS = -O2 -Wall -Wextra #-Werror
RM = rm -f

# rules
all: compile_libs create_dirs compile_libs log_compile_start $(NAME) move_tmps

compile_libs:
	@printf "\n>> compile libft\n"
	@make -C $(LIBFT_DIR) bonus

create_dirs:
	@mkdir -p tmp_files

compile_libs:
#	

-include $(DPS)

%.o: %.c
	$(CC) $(C_FLAGS) -c $< -o $@
#	$(CC) -MM $(C_FLAGS) $< > $(OBJ_DIR)/$*.d
	$(CC) -MM $(C_FLAGS) $< > $*.d

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBS) -lreadline -o $@

move_tmps:
	$(shell cp sources/*/*.o $(OBJ_DIR))
	$(shell cp sources/*/*.d $(OBJ_DIR))

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
