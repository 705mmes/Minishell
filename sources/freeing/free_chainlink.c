/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_chainlink.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:03:05 by ljerinec          #+#    #+#             */
/*   Updated: 2023/08/28 13:36:49 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	freeall(t_data *data, int status)
{
	if (!data)
		return (ERROR);
	if (status == 1)
		return (ERROR);
	else
		return (ALL_G);
}

void	free_chainlink(t_data_lst *data_parsing)
{
	if (!data_parsing->first)
		return ;
	while (data_parsing->first->next)
		ft_lstdellast(data_parsing->first);
	free(data_parsing->first);
}
