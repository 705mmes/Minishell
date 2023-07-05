/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:44:46 by ljerinec          #+#    #+#             */
/*   Updated: 2022/11/19 22:42:36 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static	int	taillenbr(int n)
{
	int	count;

	count = 2;
	while (n > 9)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static	int	isnegatif(int *n, int *neg)
{
	int	taille;

	taille = 0;
	if (*n < 0)
	{
		taille = taillenbr(*n * -1);
		*neg = 1;
		*n = *n * -1;
	}
	else
		taille = taillenbr(*n);
	return (taille);
}

char	*ft_itoa(int n)
{
	char	*memalloc;
	int		taille;
	int		neg;
	int		i;

	neg = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	taille = isnegatif(&n, &neg);
	memalloc = malloc(sizeof(char) * (taille + neg));
	if (!memalloc)
		return (NULL);
	memalloc[taille + neg - 1] = '\0';
	if (neg)
		memalloc[0] = '-';
	i = taille + neg - 2;
	while (n > 9)
	{
		memalloc[i] = n % 10 + '0';
		n = n / 10;
		i--;
	}
	memalloc[i] = n + '0';
	return (memalloc);
}
