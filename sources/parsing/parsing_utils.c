/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:22:43 by ljerinec          #+#    #+#             */
/*   Updated: 2023/07/21 13:27:31 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quoted(char *input)
{
	int	i;

	i = -1;
	if (!input)
		return (0);
	while (input[++i])
		if (input[i] == 39 || input[i] == '"')
			return (1);
	return (0);
}
