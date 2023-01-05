/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:33:14 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/05 23:09:40 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

//error
# include "error.h"
// libs
# include "tokens.h"
# include <stdio.h>
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

typedef struct s_cmd
{
	t_element			*element;
	int					exec_mode;
	int					status;
	struct s_cmd		*next;
	struct s_cmd		*prev;
}				t_cmd;

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
}	t_global;

//jnjelu
void	printlen(char *str, int len);

extern t_global	*global;

//expansion
char	*remake_var_line(char *line, int len);

//t_elem maker
void	make_struct(void);

//here doc
char	*mdn_norm(t_token *token, int flag1, int *flag, char **res);
char	*make_doc_name(t_token *token, int *flag);
int		hd_maker(t_token *token);
char	*get_pid();

//open
int	make_open(t_token **token);

//tokenization
int			first_checker(char *cmd_line);
int			*tokenization(char *cmd_line);
void		fnorm_tokenizer(char *cmd_line, int *arr, int len, int *i);
void		fnorm_tokenizer2(char *cmd_line, int *arr, int len, int *i);
void		quot_editor(int *arr, int len);
//void	ft_tokadd_back(t_token **tok, t_token *new);

//cmd init
int			get_cmd_count(int *arr);
t_element	**cmd_init(char *line, int *arr);
int			arg_counter(int *i, int *arr);
void		get_cmd_name(int *i, int *arr, t_element *elem, char *line);
void		get_cmd_args(int *i, int *arr, t_element *elem, char *line);
//utils
char		*ft_str_start_trim(char const *s1, char const *set);
void		skip_spaces(int *i, int *arr);
int			empty_line(char *line);
char	*ft_free_strjoin(char *s1, char *s2);
void print_elem(t_element *elem);
//variable expansion
char	*get_env_value(t_env *env, char *str, int *i);
void	get_var_cmd(t_env *env, t_command *cmd);
char	*change_var_cmd(char *str, int *i, t_env *env);
char	*get_env_value(t_env *env, char *str, int *i);

//env 
void	add_hidden_values(t_env **env_new);
t_env	*pars_env(char **env);
char	**get_arr_env(t_env *l_env);

//expansion
void	get_variables(t_env *env, t_element **elem);

t_token	*lexer(char *line);

#endif
