/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:35:31 by ljerinec          #+#    #+#             */
/*   Updated: 2023/08/01 18:54:12 by ljerinec         ###   ########.fr       */
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

# define TRUE 1
# define FALSE 0

# define ERROR 1
# define ALL_G 0

// Struct contenant un maillon du parsing
typedef struct s_content
{
	char	*word;
	int		index;
	int		is_env_var;
	int		is_cmd;
	int		is_flag;
	int		is_arg;
	int		is_separator;
	int		is_redir;
	int		is_squote;
	int		is_dquote;
}	t_content;

// Struct contenant un maillon de commandes
typedef struct s_cmds
{
	char	*cmd;
	char	*arg;
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
	char		*path;
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
t_data		*setup_data(char **env);
void		parsing(t_data *big_data);
t_data_lst	*create_data_lst(void);
t_content	*create_content(char *word, int i);
void		print_lst_parsing(t_list *lst_parsing);

// parsing/parsing_atribute.c
void		link_settings(t_data *big_data);
int			is_separator(t_content	*content);
int			is_flag(t_content *content);
int			is_quotes_open(char *input);
int			char_in_squotes(t_content *content, int goal);

// parsing/check_arg.c
int			check_arg(int argc, char **argv);
int			freeall(t_data *data, int status);

// parsing/parsing_utils.c
int			is_quoted(char *input);

// ft_split_fou.c
char		**ft_split_fou(char *input);

#endif