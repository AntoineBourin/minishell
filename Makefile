#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abourin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/08 13:55:47 by abourin           #+#    #+#              #
#    Updated: 2020/01/31 14:52:25 by abourin          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

SRC_NAME += main.c
SRC_NAME += command_read.c

SRC_PATH = srcs
SRCS = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

LIBFT = srcs/libft/libft.a

OBJS = ${SRCS:.c=.o}

RM = rm -f

NAME = minishell

CC = GCC

CFLAGS = -Wall -Wextra -Werror -Isrcs -Isrcs/libft

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

fclean: clean
		${RM} ${NAME}

re:		fclean all

.PHONY: all clean fclean re