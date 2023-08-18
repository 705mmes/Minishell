/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_fou_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 00:23:34 by ljerinec          #+#    #+#             */
/*   Updated: 2023/08/18 11:35:43 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	between_quotes(char	*input, int goal)
{
	int	i;
	int	state;

	i = 0;
	state = -1;
	while (input[i] && i < goal)
	{
		if (state == -1 && (input[i] == 39 || input[i] == 34))
			state = input[i];
		else if (input[i] == state)
			state = -1;
		i++;
	}
	if (state > 0)
		return (TRUE);
	return (FALSE);
}

int	is_quoted_and_who(char	*input, int goal)
{
	int		i;
	char	state;

	i = 0;
	state = -1;
	while (input[i] && i < goal)
	{
		if (state == -1 && (input[i] == 39 || input[i] == 34))
			state = input[i];
		else if (input[i] == state)
			state = -1;
		i++;
	}
	if (state == 39)
		return (39);
	else if (state == 34)
		return (34);
	else
		return (0);
}
