/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:45:18 by abiersoh          #+#    #+#             */
/*   Updated: 2023/10/31 12:45:19 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/petit_coquillage.h"

void	fill_cmd_args(t_cmd_line *cmd_line, t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == ARG)
		{
			cmd_line->cmd_args[i] = ft_strdup(token->word);
			if (!cmd_line->cmd_args[i])
				error(MALLOC_ERROR, "exec/execution.c - 1");
			i++;
		}
		token = token->next;
	}
}

void	create_args(t_cmd_line *cmd_line)
{
	int	nb_args;

	nb_args = lst_size(cmd_line);
	cmd_line->cmd_args = malloc(sizeof(char *) * (nb_args + 1));
	if (!cmd_line->cmd_args)
		error(MALLOC_ERROR, "exec/execution.c - 2");
	cmd_line->cmd_args[nb_args] = NULL;
	fill_cmd_args(cmd_line, cmd_line->token);
}

/* Retourne le nombre de variables d'environnement */
int	env_size(t_env *env)
{
	int	i;

	i = 0;
	if (env->is_first)
		env = env->next;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

/* Transforme une var d'env en char* */

char	*t_env_to_char(t_env *env)
{
	char	*dest;

	if (!env)
		printf("Probleme t_env_to_char\n");
	dest = NULL;
	dest = ft_strjoin(dest, env->var_name, 0);
	if (!dest)
		error(MALLOC_ERROR, "exec/execution.c - 4");
	dest = ft_strjoin(dest, "=", 1);
	if (!dest)
		error(MALLOC_ERROR, "exec/execution.c - 4");
	dest = ft_strjoin(dest, env->var_value, 1);
	if (!dest)
		error(MALLOC_ERROR, "exec/execution.c - 4");
	return (dest);
}

/* Cree la variable d'environnement char **env */

char	**construct_env(t_env *env)
{
	char	**dest;
	int		size;
	int		i;

	i = 0;
	size = env_size(env);
	dest = malloc((size + 1) * sizeof(char *));
	if (!dest)
		error(MALLOC_ERROR, "exec/execution.c - 3");
	dest[size] = NULL;
	if (env->is_first)
		env = env->next;
	while (i < size)
	{
		dest[i] = t_env_to_char(env);
		i++;
		env = env->next;
	}
	return (dest);
}
