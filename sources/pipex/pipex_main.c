/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:12:11 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/06 20:14:16 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_cmds(t_data *big_data)
{
	t_list		*lst;
	int			r;

	r = 0;
	lst = big_data->lst_parsing->first;
	while (lst)
	{
		if (((t_content *)lst->content)->type == CMD)
			r++;
		lst = lst->next;
	}
	return (r);
}

void	exec(t_data *big_data)
{
	if (ft_count_cmds(big_data) > 0)
		create_childs(big_data);
	else
		return (perror("No commands"), (void)1);
	print_lst_parsing(big_data->lst_parsing->first);
}
