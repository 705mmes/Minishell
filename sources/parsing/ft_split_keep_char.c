/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_keep_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 02:00:15 by ljerinec          #+#    #+#             */
/*   Updated: 2023/08/29 13:49:23 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char c)
{
	if (c == '>' || c == '<')
		return (1);
	else if (c == '|')
		return (1);
	return (0);
}

char	*go_to_next_word_keep(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!is_operator(input[i]) && !between_quotes(input, i))
			break ;
		i++;
	}
	return (input += i);
}

char	*go_to_next_operator(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (is_operator(input[i]) && !between_quotes(input, i))
			break ;
		i++;
	}
	return (input += i);
}

int	count_operator(char *input)
{
	int	i;

	i = 0;
	while (input[i] && is_operator(input[i]))
		i++;
	return (i);
}

int	len_word_keep(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (is_operator(input[i]) && !between_quotes(input, i))
			break ;
		i++;
	}
	return (i);
}

int	count_word_keep(char *input)
{
	int	wc;
	int	i;
	int	on_word;

	on_word = 0;
	i = 0;
	wc = 0;
	while (input[i])
	{
		if (!is_operator(input[i]) && on_word == 0)
		{
			wc++;
			on_word = 1;
		}
		else if (is_operator(input[i]) && !between_quotes(input, i))
		{
			wc++;
			on_word = 0;
			while (input[i + 1] && is_operator(input[i + 1]))
				i++;
		}
		i++;
	}
	return (wc);
}

char	**ft_split_keep_char(char *input)
{
	char	**array;
	int		wc;
	int		i;

	wc = count_word_keep(input);
	array = malloc(sizeof(char *) * (wc + 1));
	i = -1;
	while (++i < wc)
	{
		if (is_operator(*input))
		{
			array[i] = ft_substr(input, 0, count_operator(input));
			input = go_to_next_word_keep(input);
		}
		else
		{
			array[i] = ft_substr(input, 0, len_word_keep(input));
			input = go_to_next_operator(input);
		}
	}
	array[i] = NULL;
	return (array);
}
