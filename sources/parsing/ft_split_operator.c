/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_operator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:16:04 by ljerinec          #+#    #+#             */
/*   Updated: 2023/08/24 12:22:42 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operators_in_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
	{
		if (is_operator_in_string(array[i]))
			return (1);
	}
	return (0);
}

int	is_operator_in_string(char *str)
{
	int	i;

	i = -1;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			if (str[i + 1] && str[i] == str[i + 1])
				return (1);
			return (1);
		}
	}
	return (0);
}