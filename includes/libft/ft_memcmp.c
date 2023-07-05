/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 01:10:04 by ljerinec          #+#    #+#             */
/*   Updated: 2022/11/24 17:20:13 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(void *s1, void *s2, size_t n)
{
	size_t	i;
	char	*buffs1;
	char	*buffs2;

	buffs1 = (char *)s1;
	buffs2 = (char *)s2;
	i = 0;
	while (i < n)
	{
		if (buffs1[i] != buffs2[i])
			return ((unsigned char)buffs1[i] - (unsigned char)buffs2[i]);
		i++;
	}
	return (0);
}
