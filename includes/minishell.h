/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:35:31 by ljerinec          #+#    #+#             */
/*   Updated: 2023/07/20 12:27:27 by ljerinec         ###   ########.fr       */
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

typedef struct s_parsing
{
	char	*word;
	int		is_cmds;
	int		is_arg;
	int		is_pipe;
	int		is_redir;
	int		is_semicolon;
}	t_content;

typedef struct s_cmds
{
	char	*cmd;
	char	*arg;
	char	*infile;
	char	*outfile;
}	t_cmds;

typedef struct s_data_lst
{
	t_list	*first;
	t_list	*last;
	int		num_link;
}	t_data_lst;

typedef struct s_data
{
	char		*read_name;
	char		*path;
	char		*input;
	int			error;
	int			quotes_open;
	t_data_lst	*lst_parsing;
	t_data_lst	*lst_cmds;
}	t_data;

// prompt/prompt.c
void		prompt(t_data *big_data);

// prompt/signal.c
void		ft_signal(void);
void		sig_handler(int sig, siginfo_t *info, void *context);

// parsing/parsing.c
t_data		*setup_data(char **env);
void		parsing(t_data *big_data);
t_data_lst	*create_data_lst(void);
t_content	*create_content(char *word);
void		print_lst_parsing(t_list *lst_parsing);

// parsing/parsing_atribute.c
void		link_settings(t_data *big_data);
int			is_separator(t_content	*content);
int			is_arg(t_content *content);

// parsing/check_arg.c
int			check_arg(int argc, char **argv);
int			freeall(t_data *data, int status);

#endif