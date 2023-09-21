/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:35:01 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/21 03:14:50 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rm_quotes(char *word, int q1, int q2)
{
	char	*new_word;
	int		i;
	int		u;

	i = 0;
	u = 0;
	new_word = malloc(sizeof(char) * (ft_strlen(word) - 1));
	if (!new_word)
		return (NULL);
	while (word[i])
	{
		if (i == q1 || i == q2)
			i++;
		else
		{
			new_word[u] = word[i];
			i++;
			u++;
		}
	}
	new_word[u] = 0;
	return (new_word);
}

void	quotes_killer(t_content *content)
{
	int		i;
	int		q1;
	int		q2;
	char	q_type;

	i = 0;
	q1 = 0;
	q2 = 0;
	while (content->word[i])
	{
		q_type = 0;
		if (content->word[i] == 34 || content->word[i] == 39)
		{
			q1 = find_index_from(content->word, &q_type, i);
			q2 = find_index_from(content->word, &q_type, q1 + 1);
			content->word = rm_quotes(content->word, q1, q2);
			i = q2 - 2;
		}
		i++;
	}
}

void	call_rm_quotes(t_list *lst_parsing)
{
	t_content	*content;

	while (lst_parsing)
	{
		content = (t_content *)lst_parsing->content;
		if (is_quoted(content->word))
			quotes_killer(content);
		lst_parsing = lst_parsing->next;
	}
}

int	find_index_from(char *str, char *q_type, int start)
{
	int	i;

	i = start;
	while (str[i])
	{
		if (*q_type == 0 && (str[i] == 34 || str[i] == 39))
		{
			*q_type = str[i];
			return (i);
		}
		else if (*q_type > 0 && str[i] == *q_type)
			return (i);
		i++;
	}
	return (-1);
}

int	is_quotes_open(char *input)
{
	int	i;
	int	state;

	i = 0;
	state = 0;
	while (input && input[i])
	{
		if (state == 0 && (input[i] == 39 || input[i] == 34))
			state = input[i];
		if (input[i] == state)
			state = 0;
		i++;
	}
	if (state > 0)
		return (TRUE);
	return (FALSE);
}
