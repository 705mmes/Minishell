/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_and_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:53:09 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/04 17:36:23 by ljerinec         ###   ########.fr       */
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
		if (is_redir(content))
				return (1);
		lst = lst->next;
	}
	return (0);
}

int	is_not_redir_and_file(t_list *lst)
{
	t_content	*content;

	while (lst)
	{
		content = ((t_content *)lst->content);
		if (is_redir(content))
		{
			if (lst->next == 0)
				return (1);
			if (((t_content *)lst->next->content)->type != FD)
				return (1);
		}
		lst = lst->next;
	}
	return (0);
}

void	check_file_existence(t_list *lst)
{
	// t_content	*content;

	if (is_not_redir_and_file(lst) == 1)
	{
		printf("minishell: syntax error near unexpected token\n");
		return ;
	}
	printf("Checking if file exist\n");
	while (lst)
	{
		// content = (t_content *)lst->content;
		lst = lst->next;
	}
}

void	check_redir_files(t_data *big_data)
{
	if (is_redir_in_lst(big_data->lst_parsing->first))
		check_file_existence(big_data->lst_parsing->first);	
}
