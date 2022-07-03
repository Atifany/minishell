# executable
NAME = minishell

# sources
_SRC =	builtins/commands.c			\
		builtins/commands_1.c		\
		core/core.c					\
		core/processing.c			\
		core/signals.c				\
		core/simple_exe.c			\
		core/piped_exe.c			\
		core/processing_utils.c		\
		envs/environment.c			\
		parse/parse_to_struct.c		\
		parse/parse_utils.c			\
		parse/parse.c				\
		redirects/pipe_in.c			\
		redirects/redirects_utils.c	\
		utils/class_methods.c		\
		utils/dictionary.c			\
		utils/dictionary_delete.c	\
		utils/get_next_line_utils.c	\
		utils/get_next_line.c		\
		utils/inits.c				\
		utils/utils.c				\
		utils/utils_free.c			\
		utils/func_dict_init.c		\
		utils/validation.c			\
		
SRC_DIR = sources
SRC = $(_SRC:%=$(SRC_DIR)/%)
# tmp files
OBJ = $(SRC:%.c=%.o)
DPS = $(SRC:%.c=%.d)

# libraries
LIBFT_DIR = libs/libft/
LIBFT = libft.a
LIBS = $(LIBFT:%=$(LIBFT_DIR)%)

# Make commands
CC = gcc
C_FLAGS = -O2 -Wall -Wextra -Werror -Wno-unused-result
RM = rm -f

# rules
all: compile_libs log_compile_start $(NAME)

compile_libs:
	@printf "\n>> compile libft\n"
	@make -C $(LIBFT_DIR) bonus

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBS) -lreadline -o $@

%.o: %.c Makefile
	$(CC) $(C_FLAGS) -MMD -MP -c $< -o $@

-include $(DPS)

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
