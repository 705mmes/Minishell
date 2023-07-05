/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 18:16:59 by ljerinec          #+#    #+#             */
/*   Updated: 2023/01/21 00:59:09 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	countword(char *s, char c)
{
	int	i;
	int	counter;
	int	caracterbefore;

	caracterbefore = 0;
	counter = 0;
	i = 0;
	if (c == 0 && s[0] == 0)
		return (0);
	if (c == '\0')
		return (1);
	while (s[i])
	{
		if (c != s[i])
			caracterbefore = 1;
		if (caracterbefore && s[i] == c)
		{
			counter++;
			caracterbefore = 0;
		}
		i++;
	}
	if (caracterbefore && s[i] == '\0')
		counter++;
	return (counter);
}

static	int	lenword(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static	char	*gotonextword(char *s, char c)
{
	while (*s == c && *s && c != '\0')
		s++;
	return (s);
}

static	void	*freeall(char **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		nbword;
	int		i;
	int		len;

	if (!s)
		return (0);
	s = gotonextword((char *)s, c);
	nbword = countword((char *)s, c);
	tab = ft_calloc(sizeof(char *), (nbword + 1));
	if (!tab)
		return (0);
	i = 0;
	len = 0;
	while (i < nbword)
	{
		s = gotonextword((char *)s + len, c);
		len = lenword((char *)s, c);
		tab[i] = ft_substr(s, 0, len);
		if (!tab[i])
			return (freeall(tab, i - 1));
		i++;
	}
	return (tab);
}
