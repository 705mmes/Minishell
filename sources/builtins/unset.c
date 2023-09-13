/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:08:45 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/13 16:26:48 by sammeuss         ###   ########.fr       */
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

