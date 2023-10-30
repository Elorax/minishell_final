/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   petit_coquillage.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 01:41:28 by abiersoh          #+#    #+#             */
/*   Updated: 2023/05/12 17:06:23 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PETIT_COQUILLAGE_H
# define PETIT_COQUILLAGE_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/incs/libft.h"

#define UPDATE 42
#define READ 43

/* PRINTF */
#define RESET "\033[0m"
#define BOLDRED "\033[1m\033[31m"
#define BOLDYELLOW  "\033[1m\033[33m"

/* ERROR */
# define MALLOC_ERROR	1			//1
# define SYNTAX_ERROR	2			//2
# define CWD_ERROR		3			//1
# define CD_ERROR		4			//1
# define CMD_NOT_FOUND	127
# define EXIT_TOO_MANY_ARGS 5		//1
# define EXIT_NUM_ARG_REQUIRED 6	//2
/* exit with numeric value -> 
return the numeric value 
OU si >= à 256 et < 0 return value %2 */

/* TYPES */
# define NONE 0	
# define ARG 1					//Word
# define FILE_IN 2 				//'<'
# define FILE_OUT 3				//'>'
# define FILE_OUT_APPEND 4		//'>>'
# define HERE_DOC 5				//'<<'
# define OPEN_FILE 6			//word after '<'
# define LIMITOR 7				//word after '<<'
# define EXIT_FILE 8			//word after '>'
# define EXIT_FILE_APPEND 9		//word after '>>'

/* PARSING */
# define LEFT_CHEVRON '<'
# define RIGHT_CHEVRON '>'
# define CLASSIC_CHAR 0 

/* STRUCTS */
typedef struct s_token 
{
	char			*word;
	int				was_quoted;
	int				type;
	int				fd;
	struct s_token	*next;
	struct s_token	*previous;
}	t_token;

typedef struct s_cmd_line
{
	char				*cmd;
	t_token				*token;
	char				**cmd_args;
	int					fd_in;
	int					fd_out;
	pid_t				pid;
	struct s_cmd_line	*next;
}	t_cmd_line;

typedef struct s_env
{
	int				is_first;
	int				env_displayable;
	char			*var_name;
	char			*var_value;
	struct s_env	*next;
	struct s_env	*previous;
}	t_env;

typedef struct s_data
{
	//char		**env;
	char		*line;
	t_cmd_line	*cmd;
	t_cmd_line	*old_cmd;
	t_env		*env;
	int			pwd_displayable;
	int			code;
}	t_data;

//t_data	g_data;
extern t_data	*g_data;
extern int		g_exit_status;

/* PROTOTYPES */
	/* UTILS */
int			error(int type_error, char *str);
int			error_type(t_cmd_line *lst);
char		*get_name(char *str);
char		*get_value(char *str);
void		free_data(t_data *data);
void		free_all_data(t_data *data);
t_env		*init_env(char **env);
void		export_env(t_env *var_env);
void   		print_env(t_env *var_env);
	/* LIST */
int			lst_create_tokens(t_cmd_line *cmd_line);
void		lst_add_front_cmd_line(t_cmd_line **lst, t_cmd_line *new);
void		lst_add_front_token(t_token **lst, t_token *new);
void		lst_add_front_env(t_env **lst, t_env *new);
void    	lst_add_back_cmd_line(t_cmd_line **lst, t_cmd_line *new);
void    	lst_add_back_token(t_token **lst, t_token *new);
void    	lst_add_back_env(t_env **lst, t_env *new);
void		lst_clear_cmd_line(t_cmd_line **lst);
void		lst_clear_token(t_token **lst);
void		lst_clear_env(t_env **lst);
void		lst_delone_cmd_line(t_cmd_line *lst);
void		lst_delone_token(t_token *lst);
void		lst_delone_env(t_env *lst);
void    	lst_replace_tkn_word(t_token *token, char *new_word);
void		lst_replace_value_env(t_env *env, char *new_value, int env_displayable);
t_env		*lst_last_env(t_env *lst);
t_env		*lst_new_env(char *name, char *value);
t_env		*lst_new_env_v2(char *str);
t_env		*lst_search(t_env *env, char *str);
t_token		*lst_last_token(t_token *lst);
t_token		*lst_new_token(char *str);
t_token		*lst_new_n_token(char *str, size_t size);
t_cmd_line	*lst_new_cmd_line(char *str);
t_cmd_line	*lst_last_cmd_line(t_cmd_line *lst);
int 		lst_size(t_cmd_line *cmd_line);
int			lst_cmd_size(t_cmd_line *cmd_line);

	/* PARSING */
int			parse_line(t_data *data);
int			is_name_valid(char *str);
int			two_pipe_detector(char *line);
int			syntax_pipes(char *line);
void		display_cmd_line(t_cmd_line *cmd_line);
void		define_type(t_cmd_line *cmd_line);
	/* PARSING TOKENS */
int			expand(t_cmd_line *cmd_line, t_env *env, int pwd_displayable);
char		*expand_word(t_token *token, t_env *env, int pwd_displayable);
int 		expand_token(t_token *token, t_env *env, int pwd_displayable);

int			lst_create_tokens(t_cmd_line *cmd_line);
void		lst_insert_token(t_token *token, t_token *to_insert);
void		lst_remove_token(t_token **token);
void		lst_print_tokens(t_token *token);
void		split_tokens(t_token **token);
t_token		*split_token(char *str);
	/* BUILTINS */
int			is_builtin(t_data *data, t_token *token);
int			builtin_env(t_data *data, int print_export);
int			builtin_export(t_data *data, t_token *token);
int			builtin_unset(t_data *data, t_token *token);
void		builtin_cd(char *dir, t_data *data);
void    	builtin_echo(t_token *token, int fd);
void		builtin_exit(t_token *token, t_data *data);
void		builtin_pwd(void);
int		builtin_dispatch(t_data *data, t_token *token, t_cmd_line *cmd);
	/* SIGNALS */
void		ctrl_b(int sigid);
void		ctrl_c(int sigid);
void		ctrl_d(int sigid);

	/* EXECUTION */
int	execute(t_data *data);
int	ft_strcmp_equal(char *s1, char *s2);
char *ft_concat_and_join(char *to_concat, char *to_join);


#endif
