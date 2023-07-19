/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:31:27 by ljerinec          #+#    #+#             */
/*   Updated: 2023/07/19 15:32:12 by ljerinec         ###   ########.fr       */
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

int	check_arg(int argc, char **argv)
{
	(void) argv;
	if (argc > 1)
		return (ERROR);
	else
		return (ALL_G);
}