/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_keep_char_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:09:56 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/16 19:11:04 by ljerinec         ###   ########.fr       */
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
	while (input[i] && i < 2 && is_operator(input[i]))
		i++;
	return (i);
}
