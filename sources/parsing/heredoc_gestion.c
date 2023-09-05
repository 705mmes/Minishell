/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_gestion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:13:52 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/05 16:44:14 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_not_delimitor_after_heredoc(t_list *lst)
{
	t_content	*content;

	while (lst)
	{
		content = ((t_content *)lst->content);
		if (content->type == HEREDOC)
		{
			if (lst->next == NULL)
			{
				printf("minishell: syntax error near unexpected token 'newline'\n");
				return (1);
			}
			else if (((t_content *)lst->next->content)->type != FD)
			{
				printf("minishell: syntax error near unexpected token %s\n",
					((t_content *)lst->next->content)->word);
				return (1);
			}
		}
		lst = lst->next;
	}
	return (0);
}

int	is_heredoc_in_lst(t_list *lst)
{
	t_content	*content;

	while (lst)
	{
		content = (t_content *)lst->content;
		if (content->type == HEREDOC)
			return (1);
		lst = lst->next;
	}
	return (0);
}

void	do_heredoc_thinks(t_list *lst)
{
	(void) lst;
	printf("gnagna mon heredoc est FAIT !\n");
}

void	heredoc_gestion(t_data *big_data)
{
	t_list	*lst;

	lst = big_data->lst_parsing->first;
	if (!is_heredoc_in_lst(lst))
		return ;
	if (!is_not_delimitor_after_heredoc(lst))
		do_heredoc_thinks(lst);
}
