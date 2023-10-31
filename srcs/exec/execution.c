/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:28:41 by abiersoh          #+#    #+#             */
/*   Updated: 2023/05/15 17:42:38 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/petit_coquillage.h"

void	child_functions(t_exec *a, t_data *data, int j, int nb_pipe)
{
	child_1(a, data, j, nb_pipe);
	dups_and_builtin(a->cmd, data);
	child_2(a, data, -1, 0);
	child_3(a, data);
	child_4(a, data);
}

int	execute(t_data *data)
{
	t_exec	a;
	int		j;
	int		nb_pipe;

	init_exec(data, &a);
	nb_pipe = lst_cmd_size(a.cmd);
	j = -1;
	if (is_builtin(data, a.cmd->token) && !a.cmd->next)
		return (handle_builtin(data, &a));
	while (a.cmd)
	{
		here_pipe_fork(&a, data, &j);
		if (a.cmd->pid == 0)
			child_functions(&a, data, j, nb_pipe);
		else
		{
			free(a.hdoc);
			a.hdoc = NULL;
			a.cmd = a.cmd->next;
		}
	}
	return (child_waiter(&a, nb_pipe));
}

char	*ft_concat_and_join(char *to_concat, char *to_join)
{
	int		i;
	int		j;
	char	*tmp;
	char	*path_to_use;

	path_to_use = NULL;
	tmp = malloc(sizeof(char) * (ft_strlen(to_concat)));
	if (!tmp)
		return (NULL);
	j = 0;
	i = 0;
	while (to_concat[i] != '=')
		i++;
	i++;
	while (to_concat[i])
		tmp[j++] = to_concat[i++];
	tmp[j++] = '/';
	tmp[j] = '\0';
	path_to_use = ft_strjoin(tmp, to_join, 0);
	free(tmp);
	return (path_to_use);
}

int	ft_strcmp_equal(char *s1, char *s2)
{
	while (*s1 == *s2 && *s1 != 0 && *s1 != '=' && *s2 != 0)
	{
		s1++;
		s2++;
	}
	if (*s1 == '=' && *s2 == 0)
		return (0);
	return (*s1 - *s2);
}
