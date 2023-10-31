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
