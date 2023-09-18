/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_chainlink.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smunio <smunio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:03:05 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/18 16:58:16 by smunio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	free(lst_parsing);
}
