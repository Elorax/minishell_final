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

void create_args(t_cmd_line *cmd_line)
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
	int	i;

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

/* ft_slash et ft_find_path importees de projet pipex */

char	*ft_slash(char *s1)
{
	char	*dest;
	int		size;

	size = ft_strlen(s1) + 2;
	dest = malloc(size);
	if (!dest)
	{
		free(s1);
		return (NULL);
	}
	ft_strlcpy(dest, s1, size - 1);
	free(s1);
	ft_strlcat(dest, "/", size);
	return (dest);
}

char	**init_path(char **envp)
{
	char	**str;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp("PATH", envp[i], 4))
		i++;
	if (envp[i] != NULL)
		str = ft_split(ft_strchr(envp[i], '/'), ':');
	else
		str = NULL;
	if (str)
	{
		i = 0;
		while (str[i])
		{
			str[i] = ft_slash(str[i]);
			if (!str[i])
			{
				ft_freesplit(str);
				return (NULL);
			}
			i++;
		}
	}
	return (str);
}


void	heredoc_write(int *pipe_tab, t_cmd_line *cmd, char *hdoc)
{
	pipe(pipe_tab);

	ft_putstr_fd("//Debugging heredoc_write\n", 2);
	cmd->fd_in = pipe_tab[0];
	ft_putstr_fd(hdoc, pipe_tab[1]);
	close(pipe_tab[1]);
}


//Renvoie 1 si la redirection est vers un heredoc, 0 sinon.
int	is_heredoc(t_cmd_line *cmd)
{
	t_token	*token;
	int		type;

	token = cmd->token;
	type = 0;
	while (token)
	{
		if (token->type == OPEN_FILE || token->type == LIMITOR)
			type = token->type;
		token = token->next;
	}
	return (type == LIMITOR);
}

/* Gere les redirections */
int	handle_redirects(t_data *data, t_cmd_line *cmd, char *hdoc)
{
	t_token	*token;
	int		pipe_tab[2];

	token = cmd->token;
	while (token)
	{
		if (token->type == EXIT_FILE)
		{
			cmd->fd_out = open(token->word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		}
		else if (token->type == EXIT_FILE_APPEND)
			cmd->fd_out = open(token->word, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else if (token->type == OPEN_FILE)
		{

			cmd->fd_in = open(token->word, O_RDONLY);
			token->fd = cmd->fd_in;
			if (access(token->word, F_OK))
			{
				ft_putstr_fd("bash: No such file or directory: ", 2);
				ft_putendl_fd(token->word, 2);
				return (1);
			}
		}
		if (token->type == EXIT_FILE || token->type == EXIT_FILE_APPEND)
		{
			token->fd = cmd->fd_out;
		}
		token = token->next;
	}
	if (is_heredoc(cmd) && hdoc && !is_builtin(data, cmd->token))
		heredoc_write(pipe_tab, cmd, hdoc);
	return (0);
}






/* Verifie que les fichiers se sont bien crees */
int	check_files(t_cmd_line *cmd, t_data *data)
{
	t_token	*token;

	token = cmd->token;
	while (token)
	{
		if (token->fd == -42 || !access(token->word, F_OK))
		{
			token = token->next;
			continue;
		}
		if (access(token->word, F_OK) != 0 && token->type == OPEN_FILE)
		{
			ft_putstr_fd(token->word, 2);
			ft_putstr_fd(": bash: No such file or directory\n", 2);
		}
		else if (access(token->word, W_OK) != 0)
		{
			ft_putstr_fd(token->word, 2);
			ft_putstr_fd(": bash: Permission denied\n", 2);
		}
		if (is_builtin(data, cmd->token))
			builtin_exit(NULL, data, 0);
		else
			return (1);
	}
	return (0);
}






int	contains_heredoc(t_token *token)
{
	while (token)
	{
		if (token->type == LIMITOR)
			return (1);
		token = token->next;
	}
	return (0);
}

char	*read_heredoc(t_token *token, char *str, t_data *data)
{
	char	*dest;
	t_token	*tkn;

	dest = NULL;
	while (1)
	{
		dest = readline(BOLDYELLOW"> "RESET);
		if (dest && !ft_strcmp(token->word, dest))
			break;
		tkn = lst_new_token(dest);
		expand_token(tkn, data->env, data->pwd_displayable);

		free(dest);
		dest = ft_strdup(tkn->word);
		lst_delone_token(tkn);
		str = ft_strjoin(str, dest, 3);
		str = ft_strjoin(str, "\n", 1);
	}
	if (dest)
		free(dest);
	return (str);
}

char	*handle_heredoc(t_cmd_line *cmd, t_data *data)
{
	char	*dest;
	t_token	*token;

	token = cmd->token;
	dest = NULL;
	if (!cmd || !token)
		return (NULL);
	while (token)
	{
		if (token->type == LIMITOR)
		{
			free(dest);
			dest = NULL;
			dest = read_heredoc(token, dest, data);
		}
		token = token->next;
	}
	if (!dest)
		dest = ft_strdup("");
	return (dest);
}

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
	return(g_exit_status);
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
		close(a->fd[j][0]);
		close(a->fd[j][1]);
	}
	if (handle_redirects(data, a->cmd, a->hdoc) || check_files(a->cmd, data))
	{
		free_all_data(data);
		free(a->hdoc);
		exit(1);	//free ?
	}
}

void	child_2(t_exec *a, t_data *data, int i, int idx)
{
	create_args(a->cmd);
	a->env = construct_env(data->env);
	a->path = init_path(a->env);
	if (a->path)
	{
		while (a->path[++i] && !a->cmd_exists && !ft_strchr(a->cmd->cmd_args[0], '/'))
		{
			free(a->path_to_use);
			a->path_to_use = ft_strjoin(a->path[i], a->cmd->cmd_args[0], 0);
			if (!a->path_to_use)
				error(MALLOC_ERROR, "execution.c\n");
//			if (!access(a->path_to_use, X_OK))
//				a->cmd_exists = 1;
			a->cmd_exists = !access(a->path_to_use, X_OK);
		}
	}
	if (ft_strchr(a->cmd->cmd_args[0], '/') != NULL || !a->path)
	{
		if (a->cmd->cmd_args[0][0] == '/')
			a->path_to_use = a->cmd->cmd_args[0];
		else
		{
			while (ft_strcmp_equal(a->env[idx], "PWD") != 0)
				idx++;
			a->path_to_use = ft_concat_and_join(a->env[idx], a->cmd->cmd_args[0]);
		}
	}
}

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
		printf("malloc a chier dans execution.c\n");
	if (!access(a->path_to_use, X_OK))
		a->cmd_exists = 1;
	else if (!access(a->path_to_use, R_OK))
		a->cmd_exists = 2;
	if (!a->cmd_exists || a->cmd_exists == 2 || ((ft_strlen(a->cmd->cmd_args[0]) == 2) && a->cmd->cmd_args[0][0] == '.' && a->cmd->cmd_args[0][1] == '.'))
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
	if ((ft_strlen(a->cmd->cmd_args[0]) == 1 ) && a->cmd->cmd_args[0][0] == '.')
		printf("bash: .: filename argument required\n.: usage: . filename [arguments]\n");
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

	for (j = 0; j < nb_pipe; j++)
	{
		close(a->fd[j][0]);
		close(a->fd[j][1]);
	}
	for (j = 0; j < nb_pipe; j++)
	{
		wait(&(a->status));
	}
	return (a->status % 255);
}

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
	if (nb_pipe > 99)
		nb_pipe = 99;
	j = -1;
	if (is_builtin(data, a.cmd->token) && !a.cmd->next)
		return(handle_builtin(data, &a));
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

char *ft_concat_and_join(char *to_concat, char *to_join)
{
	int	i;
	int	j;
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
