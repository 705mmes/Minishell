/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_chainlink.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:03:05 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/17 02:35:41 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lst_content(t_data_lst *lst_parsing);

void	shell_freeall(t_data *big_data)
{
	if (!big_data)
		return ;
	free_lst_content(big_data->lst_parsing);
}

void	free_lst_content(t_data_lst *lst_parsing)
{
	t_content	*cont;
	t_list		*lst;

	lst = lst_parsing->first;
	if (!lst)
		return ;
	while (lst)
	{
		cont = (t_content *)lst->content;
		cont->to_delete = 1;
		lst = lst->next;
	}
	node_to_del(lst_parsing);
}
