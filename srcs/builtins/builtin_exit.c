/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 08:58:15 by abiersoh          #+#    #+#             */
/*   Updated: 2023/05/15 15:27:43 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/petit_coquillage.h"

/*static int	nb_args(char **arg)
{
	int	i;

	while (arg[i])
		i++;
	return (i);
}*/

static int	is_it_num(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

static int	nb_args(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		i += token->type == ARG;
		token = token->next;
	}
	return (i);
}

void	builtin_exit(t_token *token, t_data *data, int value)
{
	while (token && token->type != ARG)
		token = token->next;
	if (token == NULL)
	{	
		rl_clear_history();
		free_all_data(data);
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	if (!is_it_num(token->word))
	{
		rl_clear_history();
		error(EXIT_NUM_ARG_REQUIRED, token->word);
		free_all_data(data);
		exit(EXIT_FAILURE);
	}
	if (nb_args(token) > 1)
		error(EXIT_TOO_MANY_ARGS, NULL);
	if (nb_args(token) > 1)
		return ;
	value = ft_atoi(token->word) % 256;
	ft_putstr_fd("exit\n", 1);
	free_all_data(data);
	exit(value);
}
