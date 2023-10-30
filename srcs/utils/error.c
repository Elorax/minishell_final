/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:01:32 by abiersoh          #+#    #+#             */
/*   Updated: 2023/03/30 09:01:33 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/petit_coquillage.h"

int	error_type(t_cmd_line *lst)
{
	t_token	*cursor;

	if (!lst)
		return (0);
	while (lst)
	{
		cursor = lst->token;
		while (cursor)
		{
			if (cursor->next)
			{
				if (cursor->type >= 2 && cursor->type <= 5
					&& cursor->next->type >= 2 && cursor->next->type <= 5)
					return (cursor->next->type);
			}
			else if (cursor->type >= 2 && cursor->type <= 5)
				return (1 + 5 * (lst->next != NULL));
			cursor = cursor->next;
		}
		lst = lst->next;
	}
	return (0);
}

int	more_error(int type_error, char *str)
{
	if (type_error == CD_ERROR)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(str, 2);
		type_error = 1;
	}
	else if (type_error == EXIT_TOO_MANY_ARGS)
	{
		ft_putendl_fd("exit", 2);
		ft_putendl_fd("bash: exit: too many arguments", 2);
		type_error = 1;
	}
	else if (type_error == EXIT_NUM_ARG_REQUIRED)
	{
		ft_putendl_fd("exit", 2);
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": numeric argument required", 2);
		type_error = 2;
	}
	return (type_error);
}

int	error(int type_error, char *str)
{
	if (type_error == MALLOC_ERROR)
	{
		ft_putstr_fd("Malloc error in file: ", 2);
		ft_putendl_fd(str, 2);
	}
	else if (type_error == SYNTAX_ERROR)
	{
		ft_putstr_fd("bash: syntax error near unexpected token '", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("'", 2);
	}
	else if (type_error == CWD_ERROR)
	{
		ft_putendl_fd("pwd: cannot get current directory path", 2);
		type_error = 1;
	}
	else
		type_error = more_error(type_error, str);
	return (type_error);
}
