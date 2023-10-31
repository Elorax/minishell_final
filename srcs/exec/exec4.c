/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:45:31 by abiersoh          #+#    #+#             */
/*   Updated: 2023/10/31 12:45:32 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/petit_coquillage.h"

void	init_exec(t_data *data, t_exec *a)
{
	a->status = 0;
	a->hdoc = NULL;
	a->path_to_use = NULL;
	a->cmd = data->cmd;
	a->env = NULL;
	a->cmd_exists = 0;
}

int	handle_builtin(t_data *data, t_exec *a)
{
	g_exit_status = 0;
	if (contains_heredoc(a->cmd->token))
		a->hdoc = handle_heredoc(a->cmd, data);
	if (!handle_redirects(data, a->cmd, a->hdoc))
		if (!check_files(a->cmd, data))
			builtin_dispatch(data, a->cmd->token, a->cmd);
	free(a->hdoc);
	return (g_exit_status);
}

void	here_pipe_fork(t_exec *a, t_data *data, int *j)
{
	(*j)++;
	if (contains_heredoc(a->cmd->token))
		a->hdoc = handle_heredoc(a->cmd, data);
	if (pipe(a->fd[*j]) == -1)
	{
		perror("pipe");
		free_all_data(data);
		exit(1);
	}
	a->cmd->pid = fork();
	if (a->cmd->pid == -1)
	{
		error(1, 0);
		free_all_data(data);
		exit(1);
	}
}

void	child_1(t_exec *a, t_data *data, int j, int nb_pipe)
{
	signal(SIGINT, &ctrl_c);
	signal(SIGQUIT, &ctrl_c);
	if (j > 0)
	{
		dup2(a->fd[j - 1][0], STDIN_FILENO);
		close(a->fd[j - 1][0]);
		close(a->fd[j - 1][1]);
	}
	if (j < nb_pipe - 1)
	{
		dup2(a->fd[j][1], STDOUT_FILENO);
	}
	close(a->fd[j][0]);
	close(a->fd[j][1]);
	if (handle_redirects(data, a->cmd, a->hdoc) || check_files(a->cmd, data))
	{
		free_all_data(data);
		free(a->hdoc);
		exit(1);
	}
}

void	child_2(t_exec *a, t_data *data, int i, int idx)
{
	create_args(a->cmd);
	a->env = construct_env(data->env);
	a->path = init_path(a->env);
	while (a->path && a->path[++i] && !a->cmd_exists
		&& !ft_strchr(a->cmd->cmd_args[0], '/'))
	{
		free(a->path_to_use);
		a->path_to_use = ft_strjoin(a->path[i], a->cmd->cmd_args[0], 0);
		if (!a->path_to_use)
			error(MALLOC_ERROR, "execution.c\n");
		a->cmd_exists = !access(a->path_to_use, X_OK);
	}
	if (ft_strchr(a->cmd->cmd_args[0], '/') != NULL || !a->path)
	{
		if (a->cmd->cmd_args[0][0] == '/')
			a->path_to_use = a->cmd->cmd_args[0];
		else
		{
			while (ft_strcmp_equal(a->env[idx], "PWD") != 0)
				idx++;
			a->path_to_use = ft_concat_and_join(a->env[idx],
					a->cmd->cmd_args[0]);
		}
	}
}
