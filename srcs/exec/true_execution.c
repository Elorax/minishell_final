/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:28:41 by abiersoh          #+#    #+#             */
/*   Updated: 2023/05/12 17:06:36 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/petit_coquillage.h"



/* Fonctions importees de pipex, a ranger plus tard. */
















/* Rempli le char ** cmd_args avec les arguments
de tous les tokens de la liste chainee. */

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





/* Gere les redirections */
int	handle_redirects(t_cmd_line *cmd)
{
	t_token	*token;

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
	return (0);
	//Fonction a completer avec verification des ouvertures de fichiers.
}






/* Verifie que les fichiers se sont bin crees */
int	check_files(t_cmd_line *cmd, t_data *data)
{
	t_token	*token;

	token = cmd->token;
	while (token)
	{
		if (token->fd == -42 || !access(token->word, F_OK))	//Pas un fichier ou fichier ouvert correctement.
		{
			token = token->next;
			continue;
		}
		if (access(token->word, F_OK) != 0 && token->type == OPEN_FILE)	//fichier d'entree non existant
		{
			ft_putstr_fd(token->word, 2);
			ft_putstr_fd(": bash: No such file or directory\n", 2);
		}
		else if (access(token->word, W_OK) != 0)	//Fichier de sortie mal ouvert. pas les droits ?
		{
			ft_putstr_fd(token->word, 2);
			ft_putstr_fd(": bash: Permission denied\n", 2);
		}
		if (is_builtin(data, cmd->token))	//on etait sur un builtin : on ex
			builtin_exit(NULL, data);	//maybe a changer
		else
			return (1);
	}
	return (0);
	//Fonction a completer
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

	dest = NULL;
	if (str)
	{
		free(str);
		str = NULL;
	}
	while (1)
	{
		dest = readline(BOLDYELLOW"> "RESET);
		if (dest && !ft_strcmp(token->word, dest))
			break;
		dest = expand_word(dest, data->env, data->pwd_displayable);
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
			dest = read_heredoc(token, dest, data);
		token = token->next;
	}
	if (!dest)
		dest = ft_strdup("");
	return (dest);
}

int	execute(t_data *data)
{
	int		fd[2];
	t_cmd_line *cmd;
	int		fdd;
	char	*path_to_use;	//data->path_to_use dans projet pipex.
	char	**env;
	char	**path;
	char	*hdoc;

	hdoc = NULL;
	path_to_use = NULL;
	fdd = dup(STDIN_FILENO);
	cmd = data->cmd;
	env = NULL;
	printf("Debut de l'execution\n-----------------------\n");



	if (is_builtin(data, cmd->token) && !cmd->next)
	{
		if (contains_heredoc(cmd->token))
			hdoc = handle_heredoc(cmd, data);
		if (hdoc)
			ft_putstr_fd(hdoc, 2);
		if (!handle_redirects(cmd))
			if (!check_files(cmd, data))
				builtin_dispatch(data, cmd->token, cmd);
		cmd = cmd->next;
	} 
	while (cmd)
	{
		pipe(fd);
		cmd->pid = fork();
		if (cmd->pid == -1)
			error(1, 0);	//A changer pour mettre vraie gestion d'erreur.
		else if (cmd->pid == 0)	//On est dans le child.
		{
			/* dup2's */
			{
				if (cmd != data->cmd)	//Si pas premiere commande
					dup2(fdd, STDIN_FILENO);
				if (cmd->next)			//Si pas derniere commande
					dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
				close(fd[0]);
			}

			/* Redirections */
			{
				if (handle_redirects(cmd) || check_files(cmd, data))
					exit(1);	// frees ?
			}

			{
				dup2(cmd->fd_in, STDIN_FILENO);	//Utile si redirections
				if (is_builtin(data, cmd->token))
				{
					builtin_dispatch(data, cmd->token, cmd);
					builtin_exit(NULL, data);
				}
				dup2(cmd->fd_out, STDOUT_FILENO);
			}











		//	dup2(fdd, 0);	//On remplace l'entree standard (0) par fdd.
		//	if (cmd->next && cmd->next->cmd)
		//		dup2(fd[1], 1);		//On remplace la sortie standard (1) par fd[1].
		//	close(fd[0]);
			//Construction des parametres d'execve (voir pipex)
			{
				create_args(cmd);	//creation arguments sous forme char **
				env = construct_env(data->env);	//Creation var env sous forme char **
				path = init_path(env);	
				
				
				
				
				
				/* Creation de path to use */
				
				
				int	i;
				int cmd_exists = 0;
				i = -1;
				int	idx = 0;
				while (path[++i] && !cmd_exists)
					{
					free(path_to_use);
					if (ft_strchr(cmd->cmd_args[0], '/') != NULL)
					{
						while (ft_strcmp_equal(env[idx], "PWD") != 0)
							idx++;
						path_to_use = ft_concat_and_join(env[idx], cmd->cmd_args[0]);
					}
					else
						path_to_use = ft_strjoin(path[i], cmd->cmd_args[0], 0);
					printf("path_to_use : %s\n", path_to_use);
					if (!path_to_use)
						printf("malloc a chier dans execution.c\n");
					if (!access(path_to_use, X_OK))
						cmd_exists = 1;
				}
				if (!cmd_exists)
				{
					printf("bash: command not found: %s\n", cmd->cmd_args[0]);
					exit(1);	//Peut etre changer code de retour
				}
				execve(path_to_use, cmd->cmd_args, env);
				printf("on vient jamais ici\n");
				exit(1);	//execve s'est mal passé
			}
		}
		else	//On est dans le parent
		{
			wait(NULL);	//On attend les enfants, 
			close(fd[1]);
			fdd = fd[0];
			cmd = cmd->next;
		}
	}
	return (0);	//Peut etre pas 0
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
