/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:08:45 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/13 17:02:58 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_content *content, t_data *big_data)
{
	char	*arg;

	if (!content->cmd[1])
		return ;
	arg = ft_getenv(big_data, content->cmd[1]);
}

