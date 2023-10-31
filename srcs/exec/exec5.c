/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:45:35 by abiersoh          #+#    #+#             */
/*   Updated: 2023/10/31 12:45:36 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/petit_coquillage.h"

int	determine_status(t_exec *a)
{
	if (!ft_strchr(a->cmd->cmd_args[0], '/') && a->path)
	{
		printf("bash: %s: command not found\n", a->cmd->token->word);
		return (127);
	}
	else
	{
		if (a->cmd_exists == 2)
		{
			printf("bash: %s: premission denied\n", a->cmd->token->word);
			return (126);
		}
		else if (a->cmd_exists == 1 || !a->path)
		{
			printf("bash: %s: no such file or directory\n", a->cmd->token->word);
			return (1);
		}
		else
		{
			printf("bash: %s: command not found\n", a->cmd->token->word);
			return (127);
		}
	}
}

void	child_3(t_exec *a, t_data *data)
{
	if (!a->path_to_use && a->path)
		printf("malloc error in exec5.c\n");
	if (!access(a->path_to_use, X_OK))
		a->cmd_exists = 1;
	else if (!access(a->path_to_use, R_OK))
		a->cmd_exists = 2;
	if (!a->cmd_exists || a->cmd_exists == 2
		|| ((ft_strlen(a->cmd->cmd_args[0]) == 2)
			&& a->cmd->cmd_args[0][0] == '.'
		&& a->cmd->cmd_args[0][1] == '.'))
	{
		a->status = determine_status(a);
		if (a->env)
			ft_freesplit(a->env);
		if (a->path)
			ft_freesplit(a->path);
		free(a->hdoc);
		free(a->path_to_use);
		rl_clear_history();
		free_all_data(data);
		exit(a->status);
	}
}

void	child_4(t_exec *a, t_data *data)
{
	execve(a->path_to_use, a->cmd->cmd_args, a->env);
	perror("exec");
	if ((ft_strlen(a->cmd->cmd_args[0]) == 1) && a->cmd->cmd_args[0][0] == '.')
	{
		printf("bash: .: filename argument required\n");
		printf(".: usage: . filename [arguments]\n");
	}
	else if (!*(a->cmd->token->word) && a->cmd->token->was_quoted)
		printf("bash: %s: command not found\n", a->cmd->token->word);
	else
		printf("bash: %s: Is a directory\n", a->cmd->token->word);
	free(a->path_to_use);
	if (a->env)
		ft_freesplit(a->env);
	if (a->path)
		ft_freesplit(a->path);
	free(a->hdoc);
	rl_clear_history();
	free_all_data(data);
	exit(1);
}

void	dups_and_builtin(t_cmd_line *cmd, t_data *data)
{
	dup2(cmd->fd_in, STDIN_FILENO);
	if (is_builtin(data, cmd->token))
	{
		builtin_dispatch(data, cmd->token, cmd);
		rl_clear_history();
		free_all_data(data);
		exit(g_exit_status);
	}
	dup2(cmd->fd_out, STDOUT_FILENO);
}

int	child_waiter(t_exec *a, int nb_pipe)
{
	int	j;

	j = 0;
	while (j < nb_pipe)
	{
		close(a->fd[j][0]);
		close(a->fd[j][1]);
		wait(&(a->status));
		j++;
	}
	return (a->status % 255);
}
