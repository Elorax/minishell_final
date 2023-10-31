/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:45:22 by abiersoh          #+#    #+#             */
/*   Updated: 2023/10/31 12:45:23 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/petit_coquillage.h"

/* ft_slash et ft_find_path importees de projet pipex */

char	*ft_slash(char *s1)
{
	char	*dest;
	int		size;

	size = ft_strlen(s1) + 2;
	dest = malloc(size);
	if (!dest)
	{
		free(s1);
		return (NULL);
	}
	ft_strlcpy(dest, s1, size - 1);
	free(s1);
	ft_strlcat(dest, "/", size);
	return (dest);
}

char	**init_path(char **envp)
{
	char	**str;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp("PATH", envp[i], 4))
		i++;
	if (envp[i] != NULL)
		str = ft_split(ft_strchr(envp[i], '/'), ':');
	else
		str = NULL;
	if (str)
	{
		i = 0;
		while (str[i])
		{
			str[i] = ft_slash(str[i]);
			if (!str[i])
			{
				ft_freesplit(str);
				return (NULL);
			}
			i++;
		}
	}
	return (str);
}

void	heredoc_write(int *pipe_tab, t_cmd_line *cmd, char *hdoc)
{
	pipe(pipe_tab);
	cmd->fd_in = pipe_tab[0];
	ft_putstr_fd(hdoc, pipe_tab[1]);
	close(pipe_tab[1]);
}

//Renvoie 1 si la redirection est vers un heredoc, 0 sinon.
int	is_heredoc(t_cmd_line *cmd)
{
	t_token	*token;
	int		type;

	token = cmd->token;
	type = 0;
	while (token)
	{
		if (token->type == OPEN_FILE || token->type == LIMITOR)
			type = token->type;
		token = token->next;
	}
	return (type == LIMITOR);
}

/* Gere les redirections */

int	handle_open(t_cmd_line *cmd, t_token *token)
{
	cmd->fd_in = open(token->word, O_RDONLY);
	token->fd = cmd->fd_in;
	if (access(token->word, F_OK))
	{
		ft_putstr_fd("bash: No such file or directory: ", 2);
		ft_putendl_fd(token->word, 2);
		return (1);
	}
	return (0);
}
