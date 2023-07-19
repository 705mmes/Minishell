/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_atribute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:56:15 by ljerinec          #+#    #+#             */
/*   Updated: 2023/07/19 16:41:53 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	link_settings(t_data *big_data)
{
	t_list		*lst_parsing;
	t_content	*content;

	lst_parsing = big_data->lst_parsing->first;
	while (lst_parsing)
	{
		content = (t_content *)lst_parsing->content;
		if (!is_separator(content))
			if (!is_arg(content))
				big_data->error = TRUE;
			// 	if (!bultin(content))
			// 		if (!is_cmds(content))
		lst_parsing = lst_parsing->next;
	}
}

int	is_separator(t_content	*content)
{
	char	*word;

	word = content->word;
	if (!strncmp(word, "|", ft_strlen(word)))
		return (content->is_pipe = TRUE);
	else if (!strncmp(word, "<", ft_strlen(word))
		|| !strncmp(word, ">", ft_strlen(word))
		|| !strncmp(word, ">>", ft_strlen(word))
		|| !strncmp(word, "<<", ft_strlen(word)))
		return (content->is_redir = TRUE);
	return (FALSE);
}

int	is_arg(t_content *content)
{
	char	*word;

	word = content->word;
	if (word[0] == '-' && ft_strlen(word) > 1)
		return (content->is_arg = TRUE);
	else
		return (FALSE);
}
