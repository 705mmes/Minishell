/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_fou_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 00:23:34 by ljerinec          #+#    #+#             */
/*   Updated: 2023/08/17 14:47:13 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	between_quotes(char	*input, int goal)
{
	int	i;
	int	state;

	i = 0;
	state = -1;
	while (input[i] && i < goal)
	{
		if (state == -1 && (input[i] == 39 || input[i] == 34))
			state = input[i];
		else if (input[i] == state)
			state = -1;
		i++;
	}
	if (state > 0)
		return (TRUE);
	return (FALSE);
}

int	is_quoted_and_who(char	*input, int goal)
{
	int		i;
	char	state;

	i = 0;
	state = -1;
	while (input[i] && i < goal)
	{
		if (state == -1 && (input[i] == 39 || input[i] == 34))
			state = input[i];
		else if (input[i] == state)
			state = -1;
		i++;
	}
	if (state == 39)
		return (39);
	else if (state == 34)
		return (34);
	else
		return (0);
}

// e"c"h'o' plouf
// je cherche la premiere quote
// je retiens sa position
// tant que j'ai pas trouver la paire/seconde quote de meme type
// j'avance 
// sinon
// j'ai la position/index des deux quotes 
// j'envoie ma string et mes 2 index a ma fonction de suppression de character a la position donné.
// void	rm_quotes(t_content *content)
// {
// 	int	i;

// 	i = 0;
// 	while (content->word[i])
// 	{
		
// 		i++;
// 	}
// }

// int	rm_from_index(t_content content, ...)
// {
	// fonction a parametre variadique pour pouvoir enlever
	// autant de caractere que l'on souhaite depuis une chaine de character
	// en passant l'index des caractere a enlever
// }

void	call_rm_quotes(t_list *lst_parsing)
{
	t_content	*content;

	while (lst_parsing)
	{
		content = (t_content *)lst_parsing->content;
		if (is_quoted(content->word))
			rm_quotes(content);
		lst_parsing = lst_parsing->next;
	}
}