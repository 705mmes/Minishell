/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_chainlink.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:03:05 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/16 19:08:43 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lst_content(t_list *lst);

void	shell_freeall(t_data *big_data)
{
	if (!big_data)
		return ;
	free_lst_content(big_data->lst_parsing->first);
}

void	free_lst_content(t_list *lst)
{
	t_content	*cont;

	if (!lst)
		return ;
	while (lst)
	{
		cont = (t_content *)lst->content;
		free(cont->word);
		free(cont);
	}
}
