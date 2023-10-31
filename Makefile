# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/30 09:01:51 by abiersoh          #+#    #+#              #
#    Updated: 2023/03/30 09:01:53 by abiersoh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g3 -I.
NAME	=	minishell
LIBPATH	= 	libft/
LIB		= 	libft.a

SRCS	=	main.c								\
			export.c							\
			srcs/builtins/builtin_cd.c 			\
			srcs/builtins/builtin_echo.c 		\
			srcs/builtins/builtin_env.c			\
			srcs/builtins/builtin_exit.c 		\
			srcs/builtins/builtin_pwd.c 		\
			srcs/builtins/builtin_dispatch.c	\
			srcs/builtins/builtin_export.c		\
			srcs/builtins/builtin_unset.c		\
			srcs/lst_funs/lst_add_back.c		\
			srcs/lst_funs/lst_add_front.c		\
			srcs/lst_funs/lst_last.c			\
			srcs/lst_funs/lst_new.c				\
			srcs/lst_funs/lst_clear.c			\
			srcs/lst_funs/lst_delone.c			\
			srcs/lst_funs/lst_replace.c			\
			srcs/lst_funs/utils_env.c			\
			srcs/lst_funs/lst_size.c			\
			srcs/parsing/define_type.c 			\
			srcs/parsing/parse_line.c 			\
			srcs/parsing/parse_line_2.c 		\
			srcs/parsing/parse_line_3.c 		\
			srcs/parsing/parse_tokens.c 		\
			srcs/parsing/parse_tokens_2.c 		\
			srcs/parsing/pipe_syntax.c 			\
			srcs/parsing/expand.c				\
			srcs/parsing/expand_2.c				\
			srcs/parsing/expand_3.c				\
			srcs/signals/ctrl_b.c		 		\
			srcs/signals/ctrl_c.c		 		\
			srcs/signals/ctrl_d.c		 		\
			srcs/utils/error.c 					\
			srcs/utils/free_data.c 				\
			srcs/utils/init_env.c				\
			srcs/exec/execution.c				\

OBJS	=	$(SRCS:.c=.o)

%.o: %.c
			$(CC) $(CFLAGS) -c $< -o $@


$(NAME):	$(OBJS)
			make -C $(LIBPATH)
			$(CC) $(CFLAGS) $(OBJS) $(LIBPATH)$(LIB) -o $(NAME) -lreadline

all:		$(NAME)

leaks:		all
			valgrind --suppressions=valgrind_readline_leaks_ignore.txt	\
			--leak-check=full --show-leak-kinds=all --track-origins=yes	\
			--verbose --log-file=valgrind-out.txt ./minishell

clean:
			make -C $(LIBPATH) clean
			rm -rf $(OBJS)
			rm -rf valgrind-out.txt

fclean:		clean
			make -C $(LIBPATH) fclean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
