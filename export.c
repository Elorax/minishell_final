/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:03:21 by abiersoh          #+#    #+#             */
/*   Updated: 2023/10/31 13:03:23 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/petit_coquillage.h"

char	*cut_tab_env(char *str, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
		i++;
	str[i] = '\0';
	return (str);
}

char	*verify_end_tabenv(char *str, size_t len)
{
	size_t		i;
	char		*to_keep;

	i = 0;
	if (ft_strlen(str) != len)
	{
		while (i < len)
			i++;
		to_keep = malloc(sizeof(char) * (ft_strlen(str) - len));
		if (!to_keep)
			return (NULL);
		to_keep = str + i;
		return (to_keep);
	}
	return (NULL);
}

char	*replace_tokeep(char *tab_env, char *to_keep)
{
	size_t	i;

	i = 0;
	free(tab_env);
	tab_env = malloc(sizeof(char) * (ft_strlen(to_keep)));
	if (!tab_env)
		return (NULL);
	while (to_keep[i] != '\0')
	{
		tab_env[i] = to_keep[i];
		i++;
	}
	return (tab_env);
}

void	verify_export(char **tab_env, t_env **var_env, size_t i_tab)
{
	size_t	i;
	size_t	j;
	char	*new;
	t_env	*tmp;
	size_t	len;
	char	*to_keep;

	i = -1;
	while (++i < i_tab)
	{
		j = -1;
		new = malloc(sizeof(char) * (ft_strlen(tab_env[i])));
		if (!new)
			return ;
		while (tab_env[i][++j] != '=')
			new[j] = tab_env[i][j];
		new[j] = '\0';
		len = 0;
		tmp = (*var_env);
		while (*var_env)
		{
			if (ft_strcmp(new, (*var_env)->var_name) == 0)
			{
				len = ft_strlen((*var_env)->var_name)
					+ ft_strlen((*var_env)->var_value) + 1;
				if (verify_end_tabenv(tab_env[i], len) != NULL)
				{
					to_keep = verify_end_tabenv(tab_env[i], len);
					tab_env[i] = cut_tab_env(tab_env[i], len);
				}
			}
			(*var_env) = (*var_env)->next;
		}
		(*var_env) = tmp;
		free(new);
	}
	i = -1;
	while (++i < i_tab)
		if (!tab_env[i])
			tab_env[i] = replace_tokeep(tab_env[i], to_keep);
	free(to_keep);
}

void	replace_first_export_env(char **tab_env)
{
	int		i;
	char	*tmp_first;
	int		j;

	i = 0;
	j = 1;
	tmp_first = tab_env[i];
	while (ft_strcmp(tmp_first, tab_env[j]) >= 0)
		j++;
	while (i < j - 1)
	{
		tab_env[i] = tab_env[i + 1];
		i++;
	}
	tab_env[i] = tmp_first;
}

void	sort_export_env(char **tab_env, int len)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(tab_env[i], tab_env[j]) < 0)
				j++;
			else
			{
				tmp = tab_env[i];
				tab_env[i] = tab_env[j];
				tab_env[j] = tmp;
				i = 0;
				break ;
			}
		}
		i++;
	}
}

void	printf_export_env(char **tab_env)
{
	int	i;

	i = 0;
	while (tab_env[i] != NULL)
		printf("export %s\n", tab_env[i++]);
}

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
	while (j < i)
	{
		if (tmp->is_first)
		{
			tmp = tmp->next;
			continue ;
		}
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
