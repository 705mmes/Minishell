/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 01:27:42 by ljerinec          #+#    #+#             */
/*   Updated: 2022/11/24 17:19:48 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*buffstr;
	char	cara;

	buffstr = (char *)s;
	cara = (char)c;
	i = 0;
	while (i < n)
	{
		if (buffstr[i] == cara)
			return (&buffstr[i]);
		i++;
	}
	return (NULL);
}
