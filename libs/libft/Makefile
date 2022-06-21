# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atifany <atifany@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/26 14:43:00 by atifany           #+#    #+#              #
#    Updated: 2022/06/21 16:29:02 by atifany          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar -rcs
DEPS = libft.h
NAME = libft.a

SRC_DIR = sources
OBJ_DIR = tmp_files
_SRC = ft_atoi.c ft_isalpha.c ft_isalnum.c \
       ft_isdigit.c ft_isprint.c ft_strlen.c ft_strncmp.c \
       ft_tolower.c ft_toupper.c ft_isascii.c ft_strchr.c \
       ft_strnstr.c ft_strlcpy.c ft_strlcat.c ft_memset.c \
       ft_bzero.c ft_memcpy.c ft_memchr.c ft_memcmp.c \
       ft_memmove.c ft_calloc.c ft_strdup.c ft_substr.c \
       ft_strjoin.c ft_strtrim.c ft_itoa.c ft_split.c \
       ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
       ft_putendl_fd.c ft_putnbr_fd.c ft_strrchr.c ft_isspace.c
_SRCB = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
		ft_lstmap.c

SRC = $(_SRC:%.c=$(SRC_DIR)/%.c)
SRCB = $(_SRCB:%.c=$(SRC_DIR)/%.c)

OBJB = $(_SRCB:%.c=$(OBJ_DIR)/%.o)
OBJ = $(_SRC:%.c=$(OBJ_DIR)/%.o)

all: create_dir $(NAME)

create_dir:
		@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
		$(AR) $(NAME) $?

bonus:
		@make all OBJ="$(OBJ) $(OBJB)"

clean:
		rm -f $(OBJ) $(OBJB)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: re fclean clean bonus all
