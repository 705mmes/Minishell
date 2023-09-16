/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 20:26:29 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/16 20:27:00 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(t_content *content)
{
	if (content->type == REDIR_I || content->type == REDIR_O
		|| content->type == APPEND)
		return (1);
	return (0);
}

int	is_redir_in_lst(t_list *lst)
{
	t_content	*content;

	while (lst)
	{
		content = ((t_content *)lst->content);
		if (is_redir(content) || content->type == HEREDOC)
			return (1);
		lst = lst->next;
	}
	return (0);
}

t_list	*find_next_cmd(t_list *lst)
{
	t_content	*content;

	if (lst)
		content = ((t_content *)lst->content);
	while (lst && content->type != PIPE)
	{
		content = ((t_content *)lst->content);
		if (content->type == CMD)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
