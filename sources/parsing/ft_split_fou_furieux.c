/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_fou_furieux.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:16:04 by ljerinec          #+#    #+#             */
/*   Updated: 2023/08/25 23:02:10 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	is_operators_in_array(char **array)
// {
// 	int	i;

// 	i = -1;
// 	while (array[++i])
// 	{
// 		if (is_operator_in_string(array[i]))
// 			return (1);
// 	}
// 	return (0);
// }

// int	is_operator_in_string(char *str)
// {
// 	int	i;

// 	i = -1;
// 	while (str[i])
// 	{
// 		if (str[i] == '<' || str[i] == '>')
// 		{
// 			if (str[i + 1] && str[i] == str[i + 1])
// 				return (1);
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

#include "minishell.h"

int	is_white_space(char input)
{
	if((input >= 9 && input <= 13) || input == 32)
		return (1);
	return (0);
}

int	is_operator(char input)
{
	if (input == '<' || input == '>')
		return (1);
	else if (input == '|')
		return (1);
	else
		return (0);
}
	
char	*go_to_next_space(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
		if (is_white_space(input[i]) && !between_quotes(input, i))
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

int	len_word(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
		if (is_white_space(input[i]) && !between_quotes(input, i))
			break ;
	return (i);
}

char	**ft_split_fou_furieux(char *input)
{
	char	**splited;
	// int		i;
	int		wc;
	// int		len;

	splited = NULL;
	wc = count_word(input);
	ft_printf("%d\n", wc);
	// splited = malloc(sizeof(char *) * (wc + 1));
	// i = -1;
	// while (++i < wc)
	// {
	// 	input = go_to_next_word(input);
	// 	len = len_word(input);
	// 	splited[i] = ft_substr(input, 0, len);
	// 	input = go_to_next_space(input);
	// }
	// splited[i] = NULL;
	return (splited);
}
