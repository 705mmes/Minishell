/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 02:45:33 by ljerinec          #+#    #+#             */
/*   Updated: 2022/11/30 17:15:25 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_hexa(unsigned long nbr, const char format, int *size)
{
	char			*hexa;
	unsigned long	nbr_modulo;
	static int		n;

	n = 0;
	if (format == 'X')
		hexa = "0123456789ABCDEF";
	else if (format == 'x' || format == 'p')
		hexa = "0123456789abcdef";
	if (nbr < 16 && !n)
	{
		nbr_modulo = nbr % 16;
		ft_putchar(hexa[nbr], size);
		if (*size == -1)
			n = -1;
		return ;
	}
	else
		ft_putnbr_hexa(nbr / 16, format, size);
	if (!n)
		ft_putnbr_hexa(nbr % 16, format, size);
}
