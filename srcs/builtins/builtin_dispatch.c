/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dispatch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 08:58:31 by abiersoh          #+#    #+#             */
/*   Updated: 2023/05/03 19:24:53 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/petit_coquillage.h"


int	is_builtin(t_data *data, t_token *token)
{
	if (!data || !data->cmd)
		return (0);
	while (token && token->type != ARG)
		token = token->next;
	if (token && token->type == ARG)
	{
		if (ft_strcmp(token->word, "cd") == 0)
			return (1);
		else if (ft_strcmp(token->word, "echo") == 0)
			return (1);
		else if (ft_strcmp(token->word, "env") == 0)
			return (1);
		else if (ft_strcmp(token->word, "exit") == 0)
			return (1);
		else if (ft_strcmp(token->word, "export") == 0)
			return (1);
		else if (ft_strcmp(token->word, "pwd") == 0)
			return (1);
		else if (ft_strcmp(token->word, "unset") == 0)
			return (1);
	}
	return (0);
}

int	builtin_dispatch(t_data *data, t_token *token, t_cmd_line *cmd)
{
	if (!data || !data->cmd)
		return (0);
	while (token && token->type != ARG)
		token = token->next;
	if (token && token->type == ARG)
	{
		if (ft_strcmp(token->word, "cd") == 0)
		{
            if (token->next)
                return (builtin_cd(token->next->word, data), 1);
		}
		else if (ft_strcmp(token->word, "echo") == 0)
			return (builtin_echo(token, cmd->fd_out), 1);
		else if (ft_strcmp(token->word, "env") == 0)
			return (builtin_env(data, 0), 1);
		else if (ft_strcmp(token->word, "exit") == 0)
			return (builtin_exit(token->next, data), 1);
		else if (ft_strcmp(token->word, "export") == 0)
			return (builtin_export(data, token->next), 1);
		else if (ft_strcmp(token->word, "pwd") == 0)
			return (builtin_pwd(), 1);
		else if (ft_strcmp(token->word, "unset") == 0)
			return (builtin_unset(data, token->next), 1);
	}
	return (0);
}
