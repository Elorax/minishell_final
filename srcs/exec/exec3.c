/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:45:26 by abiersoh          #+#    #+#             */
/*   Updated: 2023/10/31 12:45:27 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/petit_coquillage.h"

int	handle_redirects(t_data *data, t_cmd_line *cmd, char *hdoc)
{
	t_token	*token;
	int		pipe_tab[2];

	token = cmd->token;
	while (token)
	{
		if (token->type == EXIT_FILE)
			cmd->fd_out = open(token->word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (token->type == EXIT_FILE_APPEND)
			cmd->fd_out = open(token->word, O_CREAT
					| O_WRONLY | O_APPEND, 0644);
		else if (token->type == OPEN_FILE)
			if (handle_open(cmd, token) == 1)
				return (1);
		if (token->type == EXIT_FILE || token->type == EXIT_FILE_APPEND)
			token->fd = cmd->fd_out;
		token = token->next;
	}
	if (is_heredoc(cmd) && hdoc && !is_builtin(data, cmd->token))
		heredoc_write(pipe_tab, cmd, hdoc);
	return (0);
}

/* Verifie que les fichiers se sont bien crees */
int	check_files(t_cmd_line *cmd, t_data *data)
{
	t_token	*token;

	token = cmd->token;
	while (token)
	{
		if (token->fd == -42 || !access(token->word, F_OK))
		{
			token = token->next;
			continue ;
		}
		if (access(token->word, F_OK) != 0 && token->type == OPEN_FILE)
		{
			ft_putstr_fd(token->word, 2);
			ft_putstr_fd(": bash: No such file or directory\n", 2);
		}
		else if (access(token->word, W_OK) != 0)
		{
			ft_putstr_fd(token->word, 2);
			ft_putstr_fd(": bash: Permission denied\n", 2);
		}
		if (is_builtin(data, cmd->token))
			builtin_exit(NULL, data, 0);
		return (1);
	}
	return (0);
}

int	contains_heredoc(t_token *token)
{
	while (token)
	{
		if (token->type == LIMITOR)
			return (1);
		token = token->next;
	}
	return (0);
}

char	*read_heredoc(t_token *token, char *str, t_data *data)
{
	char	*dest;
	t_token	*tkn;

	dest = NULL;
	while (1)
	{
		dest = readline(BOLDYELLOW"> "RESET);
		if (dest && !ft_strcmp(token->word, dest))
			break ;
		tkn = lst_new_token(dest);
		expand_token(tkn, data->env, data->pwd_displayable);
		free(dest);
		dest = ft_strdup(tkn->word);
		lst_delone_token(tkn);
		str = ft_strjoin(str, dest, 3);
		str = ft_strjoin(str, "\n", 1);
	}
	if (dest)
		free(dest);
	return (str);
}

char	*handle_heredoc(t_cmd_line *cmd, t_data *data)
{
	char	*dest;
	t_token	*token;

	token = cmd->token;
	dest = NULL;
	if (!cmd || !token)
		return (NULL);
	while (token)
	{
		if (token->type == LIMITOR)
		{
			free(dest);
			dest = NULL;
			dest = read_heredoc(token, dest, data);
		}
		token = token->next;
	}
	if (!dest)
		dest = ft_strdup("");
	return (dest);
}
