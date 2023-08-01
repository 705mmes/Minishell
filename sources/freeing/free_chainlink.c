/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:03:05 by ljerinec          #+#    #+#             */
/*   Updated: 2023/08/01 16:03:29 by ljerinec         ###   ########.fr       */
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
