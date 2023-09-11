/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_atribute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:56:15 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/11 16:47:53 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Verifie si le mot est une commande
	Change son attribution is_cmd a 1 si c'est une commande
*/
int	is_cmds(t_content *content, t_list *prev)
{
	t_content	*cont_prev;

	if (prev)
		cont_prev = (t_content *)prev->content;
	if (content->index == 0)
		content->type = CMD;
	else if (prev != NULL && cont_prev->type == OPERATOR)
		content->type = CMD;
	if (content->type == CMD)
		return (TRUE);
	return (FALSE);
}

void	find_separator(t_list *lst_parsing)
{
	t_content	*content;
	char		*word;

	while (lst_parsing)
	{
		content = (t_content *)lst_parsing->content;
		word = content->word;
		if (!strncmp(word, "|", ft_strlen(word)))
			content->type = PIPE;
		else if (!strncmp(word, "||", ft_strlen(word))
			|| !strncmp(word, "&&", ft_strlen(word)))
			content->type = OPERATOR;
		else if (!strncmp(word, "<", ft_strlen(word)))
			content->type = REDIR_I;
		else if (!strncmp(word, ">", ft_strlen(word)))
			content->type = REDIR_O;
		else if (!strncmp(word, ">>", ft_strlen(word)))
			content->type = APPEND;
		else if (!strncmp(word, "<<", ft_strlen(word)))
			content->type = HEREDOC;
		lst_parsing = lst_parsing->next;
	}
}

/*
	Definie la correspondance du mot
*/
void	define_word(t_list *lst_parsing)
{
	t_content	*content;

	while (lst_parsing)
	{
		content = (t_content *)lst_parsing->content;
		if (content->type == NONE)
			if (!is_cmds(content, lst_parsing->prev))
				content->type = CMD;
		lst_parsing = lst_parsing->next;
	}
}

void	find_fd(t_list *lst_parsing)
{
	t_content	*content;
	t_content	*next_content;

	while (lst_parsing)
	{
		content = lst_parsing->content;
		if (lst_parsing->next)
			next_content = lst_parsing->next->content;
		else
			return ;
		if (content->type == REDIR_I || content->type == REDIR_O
			|| content->type == APPEND)
		{
			if (next_content->type == NONE)
				next_content->type = FD;
		}
		else if (content->type == HEREDOC)
			if (next_content->type == NONE)
				next_content->type = FD;
		lst_parsing = lst_parsing->next;
	}
}

void	pipe_syntax_checker(t_data *big_data, t_list *lst)
{
	t_content	*content;

	while (lst)
	{
		content = (t_content *)lst->content;
		if (content->type == PIPE && lst->prev == NULL)
		{
			printf("minishell: syntax error near unexpected token '%s'\n", content->word);
			big_data->syntax_error = 1;
			return ;
		}
		else if (content->type == PIPE && lst->next == NULL)
		{
			printf("minishell: syntax error near unexpected token 'newline'\n");
			big_data->syntax_error = 1;
			return ;
		}
		lst = lst->next;
	}
}

void	link_settings(t_data *big_data)
{
	t_list		*lst_parsing;

	lst_parsing = big_data->lst_parsing->first;
	find_separator(lst_parsing);
	find_fd(lst_parsing);
	define_word(lst_parsing);
	env_var_expansion(big_data, lst_parsing);
	call_rm_quotes(lst_parsing);
}
