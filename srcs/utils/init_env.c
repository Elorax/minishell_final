/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:01:43 by abiersoh          #+#    #+#             */
/*   Updated: 2023/03/30 09:01:45 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/petit_coquillage.h"

char	*get_name(char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (!env[i])
		return (ft_strdup(env));
	return (ft_substr(env, 0, i));
}

char	*get_value(char *env)
{
	int	i;
	int	begin;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (!env[i])
		return (ft_strdup(""));
	begin = i;
	while (env[i])
		i++;
	return (ft_substr(env, begin + 1, i - 1));
}

t_env	*init_env(char **env)
{
	t_env	*lst;

	lst = NULL;
	lst = lst_new_env_v2("premier=first");
	lst->is_first = 1;
	if (!lst)
		return (NULL);
	while (*env)
		lst_add_back_env(&lst, lst_new_env_v2(*env++));
	return (lst);
}
