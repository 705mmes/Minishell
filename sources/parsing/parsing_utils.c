/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:22:43 by ljerinec          #+#    #+#             */
/*   Updated: 2023/08/24 12:13:22 by ljerinec         ###   ########.fr       */
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

t_type	witch_type(char *word)
{
	if (!strncmp(word, "|", ft_strlen(word)))
		return (PIPE);
	else if (!strncmp(word, "||", ft_strlen(word)))
		return (LOGICAL_AND);
	else if (!strncmp(word, "&&", ft_strlen(word)))
		return (BIWISE_OR);
	else if (!strncmp(word, "<", ft_strlen(word)))
		return (REDIR_I);
	else if (!strncmp(word, "<<", ft_strlen(word)))
		return (HEREDOC);
	else if (!strncmp(word, ">", ft_strlen(word)))
		return (REDIR_O);
	else if (!strncmp(word, ">>", ft_strlen(word)))
		return (APPEND);
	return (NONE);
}