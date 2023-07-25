/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_fou.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 12:56:36 by ljerinec          #+#    #+#             */
/*   Updated: 2023/07/25 22:38:16 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*go_to_next_space(char *input, int is_quote, char type)
{
	if (is_quote == 1)
	{
		input++;
		while (*input != type && *input != '\0')
			input++;
		input++;
	}
	else
	{
		while (*input != ' ' && *input != '\0')
			input++;
	}
	return (input);
}

char	*go_to_next_word(char *input)
{
	while (*input == ' ' && *input != '\0')
		input++;
	return (input);
}

int	count_word(char *input)
{
	int	wc;

	wc = 0;
	if (!input)
		return (0);
	while (*input != '\0')
	{
		input = go_to_next_word(input);
		wc++;
		if (*input == '"' || *input == 39)
			input = go_to_next_space(input, 1, *input);
		else
			input = go_to_next_space(input, 0, 0);
	}
	return (wc);
}

int	len_word(char *input, int is_quote, char type)
{
	int	i;

	i = 0;
	if (is_quote == 1)
	{
		i++;
		while (input[i] != type && input[i] != '\0')
			i++;
	}
	else
	{
		while (input[i] != ' ' && input[i] != '\0')
			i++;
	}
	return (i);
}

char	**ft_split_fou(char *input)
{
	char	**splited;
	int		i;
	int		wc;
	int		len;

	wc = count_word(input);
	splited = malloc(sizeof(char *) * (wc + 1));
	i = -1;
	while (++i < wc)
	{
		input = go_to_next_word(input);
		if ((*input == '"' || *input == 39) && *input != '\0')
			len = len_word(input, 1, *input);
		else
			len = len_word(input, 0, 0);
		splited[i] = ft_substr(input, 0, len + 1);
		if ((*input == '"' || *input == 39) && *input != '\0')
			input = go_to_next_space(input, 0, *input);
		else
			input = go_to_next_space(input, 0, 0);
	}
	splited[i] = NULL;
	return (splited);
}
