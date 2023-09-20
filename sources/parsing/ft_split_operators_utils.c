/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_operators_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:09:56 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/21 01:28:03 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char c)
{
	if (c == '>' || c == '<')
		return (1);
	else if (c == '|' || c == '&')
		return (1);
	return (0);
}

int	count_operator(char *input)
{
	int	i;

	i = 0;
	if (input[i] && input[i + 1] && input[i] == input[i + 1])
		return (2);
	else
		return (1);
	return (i);
}
