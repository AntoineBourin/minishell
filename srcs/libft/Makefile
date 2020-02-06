# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nveron <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/08 10:45:41 by nveron            #+#    #+#              #
#    Updated: 2020/02/06 11:35:06 by abourin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS += ft_isascii.c
SRCS += ft_memcmp.c
SRCS += ft_putnbr_fd.c
SRCS += ft_strlcpy.c
SRCS += ft_strtrim.c
SRCS += ft_atoi.c
SRCS += ft_atoi_spe.c
SRCS += ft_isdigit.c
SRCS += ft_memcpy.c
SRCS += ft_putstr_fd.c
SRCS += ft_strlen.c
SRCS += ft_substr.c
SRCS += ft_bzero.c
SRCS += ft_split.c
SRCS += ft_isprint.c
SRCS += ft_memmove.c
SRCS += ft_strchr.c
SRCS += ft_strmapi.c
SRCS += ft_tolower.c
SRCS += ft_itoa.c
SRCS += ft_memset.c
SRCS += ft_strdup.c
SRCS += ft_strncmp.c
SRCS += ft_toupper.c
SRCS += ft_isalnum.c
SRCS += ft_memccpy.c
SRCS += ft_putchar_fd.c
SRCS += ft_strjoin.c
SRCS += ft_strnstr.c
SRCS += ft_isalpha.c
SRCS += ft_memchr.c
SRCS += ft_putendl_fd.c
SRCS += ft_strlcat.c
SRCS += ft_strrchr.c
SRCS += ft_calloc.c
SRCS += get_next_line.c
SRCS += get_next_line_utils.c
SRCS += ft_split_space.c


SRCS += ft_lstnew_bonus.c
SRCS += ft_lstadd_front_bonus.c
SRCS += ft_lstsize_bonus.c
SRCS += ft_lstlast_bonus.c
SRCS += ft_lstadd_back_bonus.c
SRCS += ft_lstdelone_bonus.c
SRCS += ft_lstclear_bonus.c
SRCS += ft_lstiter_bonus.c

OBJS = ${SRCS:.c=.o}

OBJSBONUS = ${SRCSBONUS:.c=.o}

NAME = libft.a

RM = rm -f

CC = clang

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):    ${OBJS}
			ar rc $(NAME) ${OBJS}
bonus: ${OBJSBONUS} ${OBJS}
		ar rc ${NAME} ${OBJS} ${OBJSBONUS}
%.o: %.c
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
		${RM} ${OBJS} ${OBJSBONUS}

fclean: clean
		${RM} $(NAME)

re:		fclean all

.PHONY: all clean fclean re
