/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_fou_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 00:23:34 by ljerinec          #+#    #+#             */
/*   Updated: 2023/08/17 17:37:42 by ljerinec         ###   ########.fr       */
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

int	find_index_from(char *str, char *q_type, int start)
{
	int	i;

	i = start;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			*q_type = str[i];
			return (i);
		}
		i++;
	}
	return (-1);
}

/*
	e"c"h'o' plouf
	je cherche la premiere quote
	je retiens sa position
	tant que j'ai pas trouver la paire/seconde quote de meme type
	j'avance 
	sinon
	j'ai la position/index des deux quotes 
	j'envoie ma string et mes 2 index 
	a ma fonction de suppression de 
	character a la position donné.
*/

void	rm_quotes(t_content *content)
{
	int		i;
	int		q1;
	int		q2;
	char	q_type;

	i = 0;
	q_type = 0;
	while (content->word[i])
	{
		if (content->word[i] == 34 || content->word[i] == 39)
		{
			q1 = find_index_from(content->word, &q_type, i);
			q2 = find_index_from(content->word, &q_type, q1 + 1);
			ft_printf("q1 = %d et q2 = %d\n", q1, q2);
			i = q2;
		}
		i++;
	}
}

// int	rm_from_index(t_content *content, int i1, int i2)
// {
// 	// enleve index1 et index2 d'une chaine de character
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
