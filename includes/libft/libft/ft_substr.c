/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 01:51:15 by ljerinec          #+#    #+#             */
/*   Updated: 2022/11/24 17:36:12 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	lens;
	char			*memalloc;
	size_t			i;

	i = 0;
	if (!s)
		return (0);
	memalloc = 0;
	lens = (unsigned int)ft_strlen(s);
	if (start > lens)
		len = 0;
	lens = lens - start;
	if (lens < len)
		len = lens;
	memalloc = malloc(sizeof(char) * (len + 1));
	if (!memalloc)
		return (NULL);
	while (i < len)
	{
		memalloc[i] = s[start + i];
		i++;
	}
	memalloc[i] = '\0';
	return (memalloc);
}
