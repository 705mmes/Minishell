/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdellast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:48:47 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/01 22:04:29 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdellast(t_list *lst)
{
	if (!lst)
		return ;
	while (lst->next)
		lst = lst->next;
	if (lst->prev)
		lst->prev->next = 0;
	if (lst)
	{
		lst->next = 0;
		free(lst);
	}
}
