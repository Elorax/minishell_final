/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:00:01 by abiersoh          #+#    #+#             */
/*   Updated: 2023/06/01 16:38:53 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/petit_coquillage.h"

t_token	*lst_new_token(char *str)
{
	t_token	*new_token;

	if (!str)
		return (NULL);
	new_token = malloc(sizeof(t_token) * 1);
	if (!new_token)
		return (NULL);
	new_token->word = ft_strdup(str);
	if (!new_token->word)
	{
		free(new_token);
		return (NULL);
	}
	new_token->type = NONE;
	new_token->was_quoted = 0;
	new_token->next = NULL;
	new_token->previous = NULL;
	new_token->fd = -42;
	return (new_token);
}

t_env	*lst_new_env_v2(char *str)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->var_name = get_name(str);
	if (!new_env->var_name)
	{
		free(new_env);
		return (NULL);
	}
	new_env->var_value = get_value(str);
	if (!new_env->var_value)
	{
		free(new_env->var_name);
		free(new_env);
		return (NULL);
	}
	new_env->env_displayable = !!ft_strchr(str, '=');
	new_env->next = NULL;
	new_env->previous = NULL;
	new_env->is_first = 0;
	return (new_env);
}

t_env	*lst_new_env(char *name, char *value)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env) * 1);
	if (!new_env)
		return (NULL);
	new_env->var_name = ft_strdup(name);
	if (!new_env->var_name)
	{
		free(new_env);
		return (NULL);
	}
	new_env->var_value = ft_strdup(value);
	if (!new_env->var_value)
	{
		free(new_env->var_name);
		free(new_env);
		return (NULL);
	}
	new_env->next = NULL;
	new_env->previous = NULL;
	new_env->is_first = 0;
	return (new_env);
}

t_token	*lst_new_n_token(char *str, size_t size)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->word = ft_strndup(str, size);
	if (!new_token->word)
	{
		free(new_token);
		return (NULL);
	}
	new_token->type = NONE;
	new_token->fd = -42;
	new_token->next = NULL;
	new_token->previous = NULL;
	new_token->was_quoted = 0;
	return (new_token);
}

t_cmd_line	*lst_new_cmd_line(char *str)
{
	t_cmd_line	*new_cmd_line;

	new_cmd_line = malloc(sizeof(t_cmd_line) * 1);
	if (!new_cmd_line)
		return (NULL);
	new_cmd_line->cmd = ft_strdup(str);
	if (!new_cmd_line)
	{
		free(new_cmd_line);
		return (NULL);
	}
	new_cmd_line->token = NULL;
	new_cmd_line->next = NULL;
	new_cmd_line->fd_in = STDIN_FILENO;
	new_cmd_line->fd_out = STDOUT_FILENO;
	new_cmd_line->cmd_args = NULL;
	return (new_cmd_line);
}
