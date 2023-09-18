/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_remove_if.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 21:41:51 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/18 13:59:46 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_node_to_del(t_list *lst)
{
	t_content	*content;

	while (lst)
	{
		content = (t_content *)lst->content;
		if (content->to_delete)
			return (1);
		lst = lst->next;
	}
	return (0);
}

void	remove_node(t_list **head, t_list *node_to_remove)
{
	if (*head == NULL)
		return ;
	if (*head == node_to_remove)
	{
		*head = node_to_remove->next;
		if (*head)
			(*head)->prev = NULL;
	}
	else
	{
		if (node_to_remove->prev != NULL)
			node_to_remove->prev->next = node_to_remove->next;
		if (node_to_remove->next != NULL)
			node_to_remove->next->prev = node_to_remove->prev;
	}
	if (((t_content *)node_to_remove->content)->pathed)
		free(((t_content *)node_to_remove->content)->pathed);
	free(((t_content *)node_to_remove->content)->word);
	free(node_to_remove->content);
	free(node_to_remove);
}

void	node_to_del(t_data_lst *lst_parsing)
{
	t_list		*lst;
	t_content	*content;

	lst = lst_parsing->first;
	while (is_node_to_del(lst))
	{
		content = (t_content *)lst->content;
		if (content->to_delete)
		{
			remove_node(&lst_parsing->first, lst);
			lst = lst_parsing->first;
		}
		else
			lst = lst->next;
	}
}
