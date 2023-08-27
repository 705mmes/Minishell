/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_keep_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 02:00:15 by ljerinec          #+#    #+#             */
/*   Updated: 2023/08/27 19:30:43 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static size_t	nextlen(const char *s, size_t i, char c)
// {
// 	size_t	len;

// 	len = 0;
// 	if (s[i] == c)
// 	{
// 		while (s[i] == c)
// 		{
// 			len++;
// 			i++;
// 		}
// 		return (len);
// 	}
// 	while (s[i] != c && s[i])
// 	{
// 		len++;
// 		i++;
// 	}
// 	return (len);
// }

// static size_t	wordcount(const char *s, char c)
// {
// 	size_t	count;
// 	size_t	i;

// 	i = 1;
// 	count = 0;
// 	while (s[i - 1])
// 	{
// 		if ((i != 0 && s[i - 1] != c && (s[i] == c || !s[i])) || s[i - 1] == c)
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }

// static char	*nextword(const char *s, size_t *i, char c, size_t len)
// {
// 	char	*cpy;
// 	size_t	y;

// 	y = 0;
// 	while (s[*i] == c)
// 		(*i)++;
// 	cpy = malloc(sizeof(char) * (len + 1));
// 	if (!cpy)
// 		return (NULL);
// 	while (len)
// 	{
// 		cpy[y++] = s[(*i)++];
// 		len--;
// 	}
// 	cpy[y] = '\0';
// 	return (cpy);
// }

// static char	**freeall_split(char **tab, size_t indice)
// {
// 	size_t	y;

// 	y = 0;
// 	while (y <= indice)
// 	{
// 		free(tab[y]);
// 		y++;
// 	}
// 	free(tab);
// 	return (NULL);
// }

char	*go_to_next_word_keep(char *input, char operator)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != operator && !between_quotes(input, i))
			break ;
		i++;
	}
	return (input += i);
}

char	*go_to_next_operator(char *input, char operator)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == operator && !between_quotes(input, i))
			break ;
		i++;
	}
	return (input += i);
}

int	count_operator(char *input, char operator)
{
	int	i;

	i = 0;
	while (input[i] && input[i] == operator)
		i++;
	return (i);
}

int	len_word_keep(char *input, char operator)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == operator && !between_quotes(input, i))
			break ;
		i++;
	}
	return (i);
}

int	count_word_keep(char *input, char operator)
{
	int	wc;
	int	i;
	int	on_word;

	on_word = 0;
	i = 0;
	wc = 0;
	while (input[i])
	{
		if (input[i] != operator && on_word == 0)
		{
			wc++;
			on_word = 1;
		}
		else if (input[i] == operator && !between_quotes(input, i))
		{
			wc++;
			on_word = 0;
			while (input[i + 1] && input[i + 1] == operator)
				i++;
		}
		i++;
	}
	return (wc);
}

char	**ft_split_keep_char(char *input, char operator)
{
	char	**tab;
	int		wc;
	int		i;
	tab = NULL;

	wc = count_word_keep(input, operator);
	tab = malloc(sizeof(char *) * (wc + 1));
	i = -1;
	ft_printf("%d\n", wc);
	while (++i < wc)
	{
		if (*input == operator)
		{
			tab[i] = ft_substr(input, 0, count_operator(input, operator));
			input = go_to_next_word_keep(input, operator);
		}
		else
		{
			tab[i] = ft_substr(input, 0, len_word_keep(input, operator));
			input = go_to_next_operator(input, operator);
		}
	}
	tab[i] = NULL;
	return (tab);
}
