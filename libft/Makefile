# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lea <lea@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/23 14:47:59 by lbisson           #+#    #+#              #
#    Updated: 2022/07/26 14:08:01 by lea              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS =	-Wall -Wextra -Werror -g3 -I.
CC = 		gcc
EXEC =		libft.a

SRCS = 	srcs/ft_atoi.c 			\
		srcs/ft_bzero.c 		\
		srcs/ft_calloc.c 		\
		srcs/ft_free_split.c	\
		srcs/ft_isalnum.c 		\
		srcs/ft_isalpha.c 		\
		srcs/ft_isascii.c 		\
		srcs/ft_isdigit.c 		\
		srcs/ft_isprint.c 		\
		srcs/ft_itoa.c 			\
		srcs/ft_lstadd_back.c	\
		srcs/ft_lstadd_front.c	\
		srcs/ft_lstclear.c		\
		srcs/ft_lstdelone.c		\
		srcs/ft_lstiter.c		\
		srcs/ft_lstlast.c		\
		srcs/ft_lstmap.c		\
		srcs/ft_lstnew.c		\
		srcs/ft_lstsize.c		\
		srcs/ft_memchr.c 		\
		srcs/ft_memcmp.c 		\
		srcs/ft_memcpy.c 		\
		srcs/ft_memmove.c 		\
		srcs/ft_memset.c 		\
		srcs/ft_putchar_fd.c 	\
		srcs/ft_putendl_fd.c 	\
		srcs/ft_putnbr_fd.c 	\
		srcs/ft_putstr_fd.c 	\
		srcs/ft_split_str.c		\
		srcs/ft_split_quoted.c	\
		srcs/ft_split.c 		\
		srcs/ft_strcmp.c		\
		srcs/ft_strchr.c 		\
		srcs/ft_strdup.c 		\
		srcs/ft_striteri.c 		\
		srcs/ft_strjoin.c 		\
		srcs/ft_strlcat.c 		\
		srcs/ft_strlcpy.c 		\
		srcs/ft_strlen.c 		\
		srcs/ft_strmapi.c 		\
		srcs/ft_strncmp.c 		\
		srcs/ft_strncpy.c 		\
		srcs/ft_strndup.c 		\
		srcs/ft_strnjoin.c 		\
		srcs/ft_strnstr.c 		\
		srcs/ft_strrchr.c 		\
		srcs/ft_strtrim.c 		\
		srcs/ft_substr.c 		\
		srcs/ft_tolower.c 		\
		srcs/ft_toupper.c 		\
		srcs/ft_ultoa_base.c	\
		srcs/ft_utoa_base.c 	\
		srcs/ftprintf/ft_printf.c 				\
		srcs/ftprintf/print_address.c			\
		srcs/ftprintf/print_char.c				\
		srcs/ftprintf/print_hexa_lowercase.c	\
		srcs/ftprintf/print_hexa_uppercase.c	\
		srcs/ftprintf/print_int.c				\
		srcs/ftprintf/print_percent.c			\
		srcs/ftprintf/print_str.c				\
		srcs/ftprintf/print_unsigned_int.c		\

OBJS = ${SRCS:.c=.o}

all: ${EXEC}

$(EXEC): $(OBJS)
		ar rcs ${EXEC} ${OBJS}

clean:
		rm -f ${OBJS}

fclean: clean
		rm -f ${EXEC}

re: fclean all

.PHONY: all clean fclean re
