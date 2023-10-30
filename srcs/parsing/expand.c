/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:00:32 by abiersoh          #+#    #+#             */
/*   Updated: 2023/05/06 16:14:38 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/petit_coquillage.h"

//strremove et strinsert a deplacer dans libft

static int  is_char_valid(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}

//remove les caracteres entre la position begin et la position end de la string str
//En renvoie une version allouee.
//begin compris, end non compris
char    *ft_strremove(char *str, size_t begin, size_t end)
{
	char    *dest;
	size_t  i;
	size_t	j;
	//Remettre ft_strlen
	dest = malloc(ft_strlen(str) + 1);
	if (!dest)
	{
		error(MALLOC_ERROR, "expand.c : ft_strremove");
		return (NULL);
	}
	i = 0;
	while (str[i] && i < begin)
	{
		dest[i] = str[i];
		i++;
	}
	j = i;
	while (str[i] && i < end)
		i++;
	while (str[i])
		dest[j++] = str[i++];
	dest[j] = 0;
//	free(str);
	return (dest);
}
//insere la string to_insert dans str a la place des caracteres entre begin et size.
//en renvoie une version allouee.

char    *ft_strinsert(char *str, size_t begin, size_t end, char *to_insert)
{
	size_t  size;
	size_t  i;
	size_t  j;
	char    *dest;
	char    *tmp;

	tmp = ft_strremove(str, begin, end);	//str est free dans remove
	if (!tmp)
		return (NULL);
	size = sizeof(char) * (ft_strlen(tmp) + ft_strlen(to_insert) + 1);
	i = 0;
	dest = malloc(size);
	if (!dest)
	{
		error(MALLOC_ERROR, "expand.c : ft_strinsert");
		return (NULL);
	}
	while (tmp[i] && i < begin)
	{
		dest[i] = tmp[i];
		i++;
	}
	j = 0;
	while (to_insert[j])
		dest[i++] = to_insert[j++];
	j = i - j;
	while (tmp[j])
		dest[i++] = tmp[j++];
	dest[i] = 0;
	free(tmp);
	return (dest);
}

/*
int main(int ac, char **av)
{
	char	*str;
	char	*str2;
	char	*str3;
	char	*dest;
	char	*dest2;
	char	*dest3;

	str = strdup("0123456789");
	str2 = strdup("0123456789");
	str3 = strdup("0123456789");
	dest = ft_strinsert(str, 2, 4, "des lettres");
	dest2 = ft_strinsert(str2, 0, 4, "");
	dest3 = ft_strinsert(str3, 6, 15, "aaaa aaaa");
	printf("dest : -->%s<--\n", dest);
	printf("dest2: -->%s<--\n", dest2);
	printf("dest3: -->%s<--\n", dest3);
	free(dest);
	free(dest2);
	free(dest3);
}
*/







char	*remove_char_from_string(char *str, int i)
{
	int	j;
	int	k;
	char	*dest;

	j = 0;
	k = 0;
	dest = ft_calloc(ft_strlen(str), sizeof(char));
	while (str[j])
	{
		if (j == i)
		{
			j++;
			continue;
		}
		dest[k++] = str[j++];
	}
	free(str);

	return (dest);
}


char    *expand_word(t_token *token, t_env *env, int pwd_displayable)
{
	char    quoted;
	int     i;
	char    *name;
	char    *value;
	int     begin;
	char	*dest;
	int		qust;
	char	*str;

	str = ft_strdup(token->word);
	i = -1;
	quoted = 0;
	dest = NULL;
	begin = 0;
	value = NULL;
	qust = -1;
//	printf("expanding word : %s\n", str);
	while (str[++i])
	{
		qust = -1;
//		printf("char : %c\n", str[i]);
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (quoted == str[i])
				quoted = 0;
			else if (quoted == 0)
				quoted = str[i];
			continue;
		}
		if (quoted == SIMPLE || str[i] != '$')
			continue;

		//On est sur un dollar non simple quoted
		if (!str[i + 1])
		{
			break;
		}if (!is_char_valid(str[i + 1]))
		{
			str = remove_char_from_string(str, i--);
			continue;
		}
		i++;
		/*while (str[++i] == '$') //On skip tous les dollars
			;*/
		if (str[i] && str[i] == '?')
			qust = i;
//		printf("dest provisoire : %s\n", dest);
		char pwd[256];
		ft_bzero(pwd, 256);
		dest = ft_strnjoin(dest, str + begin, i - begin - 1, 1);	//strnjoin ne doit free que dest

		if (qust >= 0)
		{
			dest = ft_strnjoin(dest, ft_itoa(g_exit_status), 3, 3);
		}
		begin = i;
		printf("%s", str);
		while (str[i] && is_char_valid(str[i]))
		{
			if (qust >= 0 && str[i] == '?')
				begin = i;
			i++;
		}
		if (qust >= 0)
			dest = ft_strnjoin(dest, str + begin + 1, i - begin - 1, 1);
		name = ft_substr(str, begin, i - begin);
		printf("name : %s, i = %d\n", name, i);
		begin = i;
		i--;
		if (!name)
		{
			error(MALLOC_ERROR, "expand.c : expand_word");
			return (NULL);  //MALLOC ERROR
		}
		if (ft_strcmp(name, "PWD") == 0 && pwd_displayable)
		{
			getcwd(pwd, 256);
		}
		else if (lst_search(env, name))
			value = lst_search(env, name)->var_value;
		else
			value = NULL;
		//printf("$%s replaced by %s\n", name, value);
		if (value)
			dest = ft_strjoin(dest, value, 1);	//strjoin doit free dest
		else if (pwd[0])
			dest = ft_strjoin(dest, pwd, 1);
		free(name);
		/*if (!str[i])
		{
			printf("COUCOUUUUUUUUUUUUUUUU\n");
			if (!dest)
				//Si on arrive ici, le mot est uniquement
				//composé d'un $ et d'une var introuvable
				return (ft_strdup(""));
			break;
		}*/
	}
	if (!dest)
		return (str);
	dest = ft_strnjoin(dest, str + begin, i - begin, 1);
	free(token->word);
	free(str);
	token->word = ft_strdup(dest);
	return (dest);
}

int expand_token(t_token *token, t_env *env, int pwd_displayable)
{
	char    *tmp;

	tmp = NULL;
	if (token->type == ARG || token->type == OPEN_FILE || token->type == EXIT_FILE || token->type == EXIT_FILE_APPEND)
	{
		tmp = expand_word(token, env, pwd_displayable);
		if (!tmp)
			return (MALLOC_ERROR);
		lst_replace_tkn_word(token, tmp);
		free(tmp);
		//		expand_word(token->word, env);
	}
	return (0);
}

int expand(t_cmd_line *cmd_line, t_env *env, int pwd_displayable)
{
	t_token *cursor;

	while (cmd_line)
	{
		cursor = cmd_line->token;
		while (cursor)
		{
			if (expand_token(cursor, env, pwd_displayable) == MALLOC_ERROR)
				return (MALLOC_ERROR);
			cursor = cursor->next;
		}
		cmd_line = cmd_line->next;
	}
	return (0);
}
