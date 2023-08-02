/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_atribute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:56:15 by ljerinec          #+#    #+#             */
/*   Updated: 2023/08/02 01:19:51 by ljerinec         ###   ########.fr       */
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
		content->is_cmd = 1;
	else if (prev != NULL && cont_prev->is_separator)
		content->is_cmd = 1;
	if (content->is_cmd)
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
			content->is_separator = 1;
		else if (!strncmp(word, "<", ft_strlen(word))
			|| !strncmp(word, ">", ft_strlen(word))
			|| !strncmp(word, ">>", ft_strlen(word))
			|| !strncmp(word, "<<", ft_strlen(word)))
			content->is_redir = 1;
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
		if (!is_cmds(content, lst_parsing->prev))
			if (!is_flag(content))
				content->is_arg = 1;
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
		return (content->is_flag = TRUE);
	else
		return (FALSE);
}

void	link_settings(t_data *big_data)
{
	t_list		*lst_parsing;

	lst_parsing = big_data->lst_parsing->first;
	find_separator(lst_parsing);
	change_env_var(lst_parsing);
	define_word(lst_parsing);
}
