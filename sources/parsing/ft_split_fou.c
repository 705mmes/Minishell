/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_fou.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 12:56:36 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/16 19:56:06 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_white_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

char	*go_to_next_space(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
		if (is_white_space(input[i]) && !between_quotes(input, i))
			break ;
	input += (i);
	return (input);
}

char	*go_to_next_word(char *input)
{
	while (is_white_space(*input) && *input != '\0')
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
		if (*input != 0 && *input != '\n')
			wc++;
		input = go_to_next_space(input);
	}
	return (wc);
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
		len = len_word(input);
		splited[i] = ft_substr(input, 0, len);
		input = go_to_next_space(input);
	}
	splited[i] = NULL;
	return (splited);
}
