/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_keep_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 02:00:15 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/16 19:11:14 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			if (input[i + 1] && is_operator(input[i + 1])
				&& input[i] != '|' && input[i + 1] != '|')
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
			input += count_operator(input);
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
