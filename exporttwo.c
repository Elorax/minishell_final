/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exporttwo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:03:21 by abiersoh          #+#    #+#             */
/*   Updated: 2023/10/31 13:03:23 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/petit_coquillage.h"

char	*ft_strlcpy_env(char *dst, const char *src, size_t size)
{
	size_t	i;
	int		j;

	i = 0;
	j = ft_strlen(dst);
	if (!size)
		return (NULL);
	dst[j++] = '\"';
	while ((i < size - 1) && src[i] != '\0')
		dst[j++] = src[i++];
	dst[j++] = '\"';
	dst[j] = '\0';
	return (dst);
}

char	*ft_strjoin_env(char *s1, char *s2, int env_displayable)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*new_str;

	if (!env_displayable)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_str = ft_calloc(sizeof(char), s1_len + s2_len + 4);
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, s1, s1_len + 1);
	new_str[s1_len] = '=';
	ft_strlcpy_env(new_str, s2, s2_len + 1);
	return (new_str);
}

int	count_env(t_env *var_env)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = var_env;
	while (tmp)
	{
		if (!tmp->is_first)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	print_env(t_env *var_env)
{
	t_env	*tmp;

	tmp = var_env;
	while (tmp)
	{
		printf("[%s] =", tmp->var_name);
		printf("[%s]\n", tmp->var_value);
		tmp = tmp->next;
	}
}

void	export_env(t_env *var_env)
{
	size_t	i;
	char	**tab_env;
	size_t	j;
	t_env	*tmp;

	j = 0;
	i = count_env(var_env);
	tab_env = malloc(sizeof(char *) * (i + 1));
	if (!tab_env)
		return ;
	tab_env[i] = NULL;
	tmp = var_env;
	if (tmp->is_first)
		tmp = tmp->next;
	while (j < i)
	{
		tab_env[j] = ft_strjoin_env(tmp->var_name,
				tmp->var_value, tmp->env_displayable);
		tmp = tmp->next;
		j++;
	}
	sort_export_env(tab_env, i);
	replace_first_export_env(tab_env);
	printf_export_env(tab_env);
	ft_freesplit(tab_env);
}
