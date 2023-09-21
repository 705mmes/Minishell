/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 03:13:20 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/21 17:09:47 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		sizetotal;
	char	*chainjoin;
	size_t	i;
	size_t	u;

	i = 0;
	u = 0;
	sizetotal = ft_strlen(s1) + ft_strlen(s2);
	chainjoin = malloc(sizeof(char) * (sizetotal + 1));
	if (!chainjoin)
		return (NULL);
	while (s1 && i < ft_strlen(s1))
	{
		chainjoin[i] = s1[i];
		i++;
	}
	while (s2 && u < ft_strlen(s2))
	{
		chainjoin[i] = s2[u];
		i++;
		u++;
	}
	chainjoin[i] = '\0';
	free(s1);
	return (chainjoin);
}
