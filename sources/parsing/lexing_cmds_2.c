/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_cmds_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:05:03 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/22 15:05:14 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*word_tolower(char *str)
{
	int			u;

	u = -1;
	while (str[++u])
		str[u] = ft_tolower(str[u]);
	return (str);
}
