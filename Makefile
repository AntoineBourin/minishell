# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/08 13:55:47 by abourin           #+#    #+#              #
#    Updated: 2020/10/02 17:43:47 by cnotin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_NAME += main.c
SRC_NAME += env_variable.c
SRC_NAME += env_variable_1.c
SRC_NAME += env_variable_2.c
SRC_NAME += env_variable_3.c
SRC_NAME += get_name_cmd.c
SRC_NAME += command_read.c
SRC_NAME += command_read_1.c
SRC_NAME += command_read_2.c
SRC_NAME += command_read_3.c
SRC_NAME += command_read_4.c
SRC_NAME += pwd.c
SRC_NAME += cd.c
SRC_NAME += translator.c
SRC_NAME += translator_1.c
SRC_NAME += unset.c
SRC_NAME += env.c
SRC_NAME += export.c
SRC_NAME += export_2.c
SRC_NAME += echo.c
SRC_NAME += echo_1.c
SRC_NAME += exit.c
SRC_NAME += redirection.c
SRC_NAME += redirection_1.c
SRC_NAME += redirection_2.c
SRC_NAME += redirection_3.c
SRC_NAME += redirection_4.c
SRC_NAME += redirection_5.c
SRC_NAME += cmdlist.c
SRC_NAME += cmdlist_1.c
SRC_NAME += ft_util_export.c
SRC_NAME += ft_utils_export_2.c
SRC_NAME += ft_parse_error.c
SRC_NAME += ft_utils_error.c
SRC_NAME += ft_utils_error_2.c
SRC_NAME += help_norm.c

SRC_PATH = srcs
SRCS = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

LIBFT = srcs/libft/libft.a

OBJS = ${SRCS:.c=.o}

RM = rm -f

NAME = minishell

CC = clang

CFLAGS = -Wall -Wextra -Werror

.c .o: 	
		@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			cd srcs/libft && make
			@${CC} ${CFLAGS} $^ -o $@ ${LIBFT}
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
