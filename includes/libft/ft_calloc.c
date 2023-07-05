/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 23:32:47 by ljerinec          #+#    #+#             */
/*   Updated: 2022/11/21 18:11:04 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*memalloc;

	memalloc = 0;
	memalloc = malloc(size * count);
	if (!memalloc)
		return (NULL);
	ft_bzero(memalloc, count * size);
	return (memalloc);
}
