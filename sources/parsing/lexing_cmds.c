/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:21:28 by ljerinec          #+#    #+#             */
/*   Updated: 2023/08/30 14:25:41 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_lst_cmds(t_data *big_data)
{
	t_list		*lst;
	t_content	*content;

	lst = big_data->lst_parsing->first;
	content = (t_content *)lst->content;
	big_data->lst_cmds = create_data_lst();
	// while (lst)
	// {
	// 	if (content->cmd_index)
	// }
}
