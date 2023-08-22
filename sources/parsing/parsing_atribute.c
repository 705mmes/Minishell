/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_atribute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:56:15 by ljerinec          #+#    #+#             */
/*   Updated: 2023/08/22 13:56:56 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Verifie si le mot est une commande
	Change son attribution is_cmd a 1 si c'est une commande
*/
int	is_cmds(t_content *content, t_list *prev)
{
	t_content	*content_prev;

	if (prev)
		content_prev = (t_content *)prev->content;
	if (content->index == 0)
		content->type = CMD;
	else if (prev != NULL && (content_prev->type == PIPE
			|| content_prev->type == FD))
		content->type = CMD;
	if (content->type == CMD)
		return (TRUE);
	return (FALSE);
}

t_type	witch_type(char *word)
{
	if (!strncmp(word, "|", ft_strlen(word)))
		return (PIPE);
	else if (!strncmp(word, "||", ft_strlen(word)))
		return (LOGICAL_AND);
	else if (!strncmp(word, "&&", ft_strlen(word)))
		return (BIWISE_OR);
	else if (!strncmp(word, "<", ft_strlen(word)))
		return (REDIR_I);
	else if (!strncmp(word, "<<", ft_strlen(word)))
		return (HEREDOC);
	else if (!strncmp(word, ">", ft_strlen(word)))
		return (REDIR_O);
	else if (!strncmp(word, ">>", ft_strlen(word)))
		return (APPEND);
	return (NONE);
}

void	define_separator(t_list *lst_parsing)
{
	t_content	*content;
	char		*word;

	while (lst_parsing)
	{
		content = (t_content *)lst_parsing->content;
		word = content->word;
		if (!strncmp(word, "|", ft_strlen(word))
			|| !strncmp(word, "||", ft_strlen(word))
			|| !strncmp(word, "&&", ft_strlen(word)))
			content->type = witch_type(word);
		else if (!strncmp(word, "<", ft_strlen(word))
			|| !strncmp(word, ">", ft_strlen(word))
			|| !strncmp(word, ">>", ft_strlen(word))
			|| !strncmp(word, "<<", ft_strlen(word)))
			content->type = witch_type(word);
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
				content->type = ARG;
		lst_parsing = lst_parsing->next;
	}
}

/*
	Verifie si le mot est un flag
	Return : 1 = true, 2 = false
*/
// int	is_flag(t_content *content)
// {
// 	char	*word;

// 	word = content->word;
// 	if (word[0] == '-' && ft_strlen(word) > 1)
// 		return (content->type = FLAG);
// 	else
// 		return (FALSE);
// }

void	define_fd(t_list *lst_parsing)
{
	t_content	*content;
	t_content	*next_content;

	while (lst_parsing)
	{
		content = lst_parsing->content;
		if (lst_parsing->next)
		{
			next_content = lst_parsing->next->content;
			if (content->type == REDIR_I || content->type == REDIR_O
				|| content->type == APPEND || content->type == HEREDOC)
				next_content->type = FD;
		}
		else
			return ;
		lst_parsing = lst_parsing->next;
	}
}

void	link_settings(t_data *big_data)
{
	t_list		*lst_parsing;

	lst_parsing = big_data->lst_parsing->first;
	define_separator(lst_parsing);
	define_fd(lst_parsing);
	define_word(lst_parsing);

	env_var_expansion(lst_parsing);
	call_rm_quotes(lst_parsing);
}
