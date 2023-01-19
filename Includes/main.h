/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:33:14 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/19 20:04:11 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

//error
# include "error.h"
// libs
# include "tokens.h"
# include <stdio.h>
# include <termios.h>
# include <errno.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <limits.h>
# include <unistd.h>
# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_command
{
	char	*cmd;
	char	**args;
	int		in;
	int		out;
	int		err;
}			t_command;

typedef struct s_element	t_element;

struct s_element
{
	t_command	*command;
	int			delimiter;
	int			type;
	t_element	*next;
}	;

// token types -> | & ; () < > SPACE TAB NEWLINE  {1..8}
// int type 0 -> is word, int type{1..8} is token
typedef struct s_token		t_token;

struct s_token
{
	int				len;
	char			*str;
	int				type;
	t_token			*next;
} ;

typedef struct s_env
{
	int				hidden;
	char			*val_name;
	char			*val_value;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

typedef struct s_global
{
	t_env		*env;	
	t_token		*tokens;
	t_element	*elem;
	int			fd_index;
	int			all_fd[OPEN_MAX];
	int			hd_count;
	int			signal;
}	t_global;

extern t_global	*g_lobal;

//////////////////////////////////////////////////////////////////////////////
//ENV
//env_charptr.c
int			get_env_var_count(t_env *l_env);
char		*get_line_env(t_env *l_env);
char		**get_arr_env(t_env *l_env);
//env_pars1.c
t_env		*pars_env(char **env);
char		*get_val_name(char *env_line);
char		*get_val(char *env_line);
//env_pars2.c
void		add_hidden_values(t_env **env_new);
void		add_env_value(char *name, char *val, int hidden, t_env **env_new);
char		*get_pid(void);
void		check_shlvl(t_env **env);
////////////////////////////////////////////////////////////////////////////
//SINGALS.c
void		handler(int signal);
void		signal_call(int i);
//////////////////////////////////////////////////////////////////////////////
//UTILS
//utils1.c
int			empty_line(char *line);
int			set_status(int status);
char		*ft_free_strjoin(char *s1, char *s2);
char		*remake_var_line(char *line, int len);
//utils2.c
int			no_var(char *line, size_t len);
int			hd_count_check(t_token * token);
char		*get_env_value(t_env *env, char *str, int *i);
////////////////////////////////////////////////////////////////////////////
//LEXER
//lexer.c
t_token		*lexer(char *line);
t_token		*ft_toknew(char *line, int type, int len);
void		ft_tokadd_back(t_token **lst, t_token *new);
//lexer_utils1.c
int			is_word_tok(char c);
void		make_word_tok(t_token **token_ptr, char *line, int *i);
void		make_pipe_tok(t_token **token_ptr, char *line, int *i);
void		make_redin_tok(t_token **token_ptr, char *line, int *i);
void		make_here_tok(t_token **token_ptr, char *line, int *i);
//lexer_utils2.c
void		make_redout_tok(t_token **token_ptr, char *line, int *i);
void		make_apply_tok(t_token **token_ptr, char *line, int *i);
void		make_space_tok(t_token **token_ptr, char *line, int *i);
void		make_dbq_tok(t_token **token_ptr, char *line, int *i);
void		make_sqt_tok(t_token **token_ptr, char *line, int *i);
//////////////////////////////////////////////////////////////////////////////
//LEX_ANALYSER
//lex_analyser.c
int			lex_analyser(t_token *token);
////OPEN
////open.c
int			make_open(t_token **tmp);
int			open_file(char *file, int flag);
char		*get_file_name(t_token *ptr);
char		*get_qtfile_name(t_token *ptr);
////HERE_DOC
////here_doc.c
int			hd_maker(t_token *token);
void		make_doc(char *doc, int flag);
char		*make_doc_name(t_token *token, int *flag);
////hd_utils1.c
char		*concate_string(t_token **token);
char		*get_dollar(void);
char		*get_doc_name(void);
void		put_in_file(char *line, int fd, int flag, size_t len);
void		hd_wait(int *status, pid_t *pid);
////////////////////////////////////////////////////////////////////////////
//MAKE_STRUCT
//make_struct.c
void		make_struct(void);
t_command	*make_cmd(t_token **tok);
void		make_elem(t_token	**tok, t_element **elem);
//make_struct_utils.c
int			arg_count(t_token *tok);
void		skip_redir(t_token **tok);
void		fill_cmd(t_command *cmd, int arg_count, t_token	**tok);
//////////////////////////////////////////////////////////////////////////////
//DESTROY_STRUCT
//destroy1.c
void		free_elem(t_element	**elem);
void		destroy_struct(void);
//destroy2.c
void		free_chardbp(char ***group);
void		close_fd(void);
void		free_cmd(t_element **elem);
void		free_token(t_token	**token);
////////////////////////////////////////////////////////////////////////////
#endif
