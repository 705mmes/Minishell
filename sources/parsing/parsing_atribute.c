/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_atribute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:56:15 by ljerinec          #+#    #+#             */
/*   Updated: 2023/08/04 01:47:52 by ljerinec         ###   ########.fr       */
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
		if (!strncmp(word, "|", ft_strlen(word))
			|| !strncmp(word, "||", ft_strlen(word))
			|| !strncmp(word, "&&", ft_strlen(word)))
			content->type = OPERATOR;
		else if (!strncmp(word, "<", ft_strlen(word))
			|| !strncmp(word, ">", ft_strlen(word))
			|| !strncmp(word, ">>", ft_strlen(word))
			|| !strncmp(word, "<<", ft_strlen(word)))
			content->type = REDIR;
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
				if (!is_flag(content))
					content->type = ARG;
		lst_parsing = lst_parsing->next;
	}
}

/*
	Verifie si le mot est un flag
	Return : 1 = true, 2 = false
*/
int	is_flag(t_content *content)
{
	char	*word;

	word = content->word;
	if (word[0] == '-' && ft_strlen(word) > 1)
		return (content->type = FLAG);
	else
		return (FALSE);
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
		if (content->type == REDIR)
			next_content->type = FD;
		lst_parsing = lst_parsing->next;
	}
}

void	link_settings(t_data *big_data)
{
	t_list		*lst_parsing;

	lst_parsing = big_data->lst_parsing->first;
	find_separator(lst_parsing);
	find_fd(lst_parsing);
	define_word(lst_parsing);
	//change_env_var(lst_parsing);
}
