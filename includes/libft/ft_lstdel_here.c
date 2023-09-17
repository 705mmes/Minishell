/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_here.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 01:22:34 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/17 01:25:29 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel_here(t_list **lst, t_list *node_to_delete)
{
	if (!lst || !*lst || !node_to_delete)
		return ;
	if (node_to_delete->prev)
		node_to_delete->prev->next = node_to_delete->next;
	else
		*lst = node_to_delete->next;
	if (node_to_delete->next)
		node_to_delete->next->prev = node_to_delete->prev;
	else
		*lst = node_to_delete->prev;
	free(node_to_delete);
}
