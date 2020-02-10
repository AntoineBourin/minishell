#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abourin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/08 13:55:47 by abourin           #+#    #+#              #
#    Updated: 2020/02/06 14:41:26 by abourin          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

SRC_NAME += main.c
SRC_NAME += command_read.c
SRC_NAME += commands/move_into_folders.c
SRC_NAME += middleware.c
SRC_NAME += commands/pwd.c
SRC_NAME += commands_result.c
SRC_NAME += commands/execute_binary.c
SRC_NAME += commands/exec_binary_with_env.c
SRC_NAME += commands/env_variable.c
SRC_NAME += args_helper.c
SRC_NAME += commands/echo.c
SRC_NAME += commands/unset.c
SRC_NAME += translator.c
SRC_NAME += redirection.c

SRC_PATH = srcs
SRCS = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

LIBFT = srcs/libft/libft.a

OBJS = ${SRCS:.c=.o}

RM = rm -f

NAME = minishell

CC = GCC

CFLAGS = -Wall -Wextra -fsanitize=address -g3 -Isrcs -Isrcs/libft

.c .o: 	
		@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			cd srcs/libft && make
			@${CC} ${CFLAGS} ${LIBFT} $^ -o $@ -fsanitize=address -g3
			@echo "Compilation of Minishell:    \033[1;32mOK\033[m"

all: ${NAME}

bonus: ${NAME}

clean:
		${RM} ${OBJS}
		cd srcs/libft && make clean

fclean: clean
		${RM} ${NAME}
		cd srcs/libft && make fclean

re:		fclean all

.PHONY: all clean fclean re