/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_here.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 00:55:51 by ljerinec          #+#    #+#             */
/*   Updated: 2023/08/31 01:06:11 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_here(t_list **lst, t_list *new)
{
	if (!*lst)
	{
		new->prev = 0;
		(*lst) = new;
	}
	else
	{
		new->prev = (*lst);
		if ((*lst)->next)
		{
			new->next = (*lst)->next;
			(*lst)->next->prev = new;
		}
		else
			new->next = NULL;
		(*lst)->next = new;
	}
}
