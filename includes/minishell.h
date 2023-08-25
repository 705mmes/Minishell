/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:35:31 by ljerinec          #+#    #+#             */
/*   Updated: 2023/08/25 22:51:33 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

# include "libft/libft.h"

# include <curses.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include <sys/wait.h>

# define TRUE 1
# define FALSE 0

# define ERROR 1
# define ALL_G 0

typedef enum s_type
{
	NONE,
	CMD,
	ARG,
	PIPE,
	LOGICAL_AND,
	BIWISE_OR,
	REDIR_I,
	REDIR_O,
	REDIR,
	APPEND,
	HEREDOC,
	FD,
}	t_type;

typedef struct s_pipe
{
	int						pipe_fd[2];
	struct s_cmd			*pipe_in;
	struct s_cmd			*pipe_out;
}	t_pipe;

typedef struct s_file
{
	int						fd;
	char					*file_name;
	int						fd_in;
	int						fd_out;
}	t_file;

typedef struct s_cmd
{
	char					**cmd;
	struct s_pipe			in_pipe;
	struct s_file			in_file;
	struct s_pipe			out_pipe;
	struct s_file			out_file;
}	t_cmd;

typedef struct s_content
{
	char	*word;
	int		index;
	int		is_expand;
	t_type	type;
}	t_content;

// Struct contenant un maillon de commandes
typedef struct s_cmds
{
	char	**cmd;
	t_list	noc_cmd;
	char	*infile;
	char	*outfile;
}	t_cmds;

// Struct contenant les adresses d'une liste chainée
typedef struct s_data_lst
{
	t_list	*first;
	t_list	*last;
	int		num_link;
}	t_data_lst;

// Stuct principale 
typedef struct s_data
{
	char		*read_name;
	char		**path;
	char		*input;
	int			error;
	t_data_lst	*lst_parsing;
	t_data_lst	*lst_cmds;
}	t_data;

// prompt/prompt.c
void		prompt(t_data *big_data);
void		use_prompt(t_data *big_data, char *input);

// prompt/signal.c
void		ft_signal(void);
void		sig_handler(int sig, siginfo_t *info, void *context);
int			is_ctrl_d(t_data *big_data, char *input);

// parsing/parsing.c
t_data_lst	*create_data_lst(void);
t_content	*create_content(char *word, int i);
t_data		*setup_data(char **env);
void		parsing(t_data *big_data);
void		print_lst_parsing(t_list *lst_parsing);

// parsing/parsing_atribute.c
// int			is_separator(t_content	*content);
int			is_flag(t_content *content);
int			is_quotes_open(char *input);
int			char_in_squotes(t_content *content, int goal);
void		link_settings(t_data *big_data);

// parsing/check_arg.c
int			check_arg(int argc, char **argv);
int			freeall(t_data *data, int status);

// parsing/parsing_utils.c
int			is_quoted(char *input);
t_type		witch_type(char *word);

// parsing/ft_split_fou.c
int			count_word(char *input);
int			len_word(char *input);
char		*go_to_next_space(char *input);
char		*go_to_next_word(char *input);
char		**ft_split_fou(char *input);

// parsing/ft_split_fou_utils.c
int			between_quotes(char	*input, int goal);
int			is_quoted_and_who(char	*input, int goal);

// parsing/env_var_expansion.c
int			is_env_var(t_content *content);
int			is_quotes_open(char *input);
void		change_env_var(t_list *lst_parsing);
void		env_to_string(t_content *content);
void		env_var_expansion(t_list *lst_parsing);

// parsing/quoting.c
char		*rm_quotes(char *word, int q1, int q2);
void		call_rm_quotes(t_list *lst_parsing);
int			find_index_from(char *str, char *q_type, int start);
void		quotes_killer(t_content *content);

// freeing/free_chainlink.c
void		free_chainlink(t_data_lst *data_parsing);

// fou_
char		**ft_split_fou_furieux(char *input);

#endif