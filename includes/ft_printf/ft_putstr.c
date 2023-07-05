/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 23:08:29 by ljerinec          #+#    #+#             */
/*   Updated: 2022/11/26 21:06:18 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr(char *s, int *size)
{
	int	i;

	i = 0;
	if (!s)
	{
		if (write(1, "(null)", 6) == -1)
		{
			*size = -1;
			return ;
		}
		*size += 6;
		return ;
	}
	while (s[i])
	{
		ft_putchar(s[i], size);
		if (*size == -1)
			return ;
		i++;
	}
}
