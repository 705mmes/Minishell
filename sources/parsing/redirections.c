/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:53:09 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/26 14:37:34 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_mini_sig;

int	is_not_redir_and_file(t_list *lst)
{
	t_content	*content;

	while (lst)
	{
		content = ((t_content *)lst->content);
		if (is_redir(content))
		{
			if (lst->next == 0)
			{
				content->to_delete = 1;
				printf("minishell: ");
				ft_putstr_fd("syntax error near unexpected token `newline'", 2);
				return (g_mini_sig = 2);
			}
			if (((t_content *)lst->next->content)->type != FD)
			{
				content->to_delete = 1;
				printf("minishell: syntax error near unexpected token `%s'\n",
					((t_content *)lst->next->content)->word);
				return (g_mini_sig = 2);
			}
		}
		lst = lst->next;
	}
	return (0);
}

void	check_type(t_content *content, t_list *current_cmd, t_list *lst)
{
	if (content->type == REDIR_O)
		check_redir_out(lst, &current_cmd);
	else if (content->type == REDIR_I)
		check_redir_in(lst, &current_cmd);
	else if (content->type == APPEND)
		check_append(lst, &current_cmd);
	else if (content->type == HEREDOC)
		check_heredoc(lst, &current_cmd);
}

void	check_perm_and_exist(t_list *lst)
{
	t_list		*current_cmd;
	t_content	*content;
	int			flag;

	flag = 0;
	current_cmd = find_next_cmd(lst);
	while (lst && !flag)
	{
		if (current_cmd == NULL)
			flag = 1;
		while (lst && ((t_content *)lst->content)->type != PIPE)
		{
			content = ((t_content *)lst->content);
			if (!current_cmd)
				check_no_cmd(lst);
			else
				check_type(content, current_cmd, lst);
			lst = lst->next;
		}
		while (lst && ((t_content *)lst->content)->type == PIPE)
			lst = lst->next;
		current_cmd = find_next_cmd(lst);
		if (lst == NULL || current_cmd == NULL)
			flag = 1;
	}
}

void	check_file_existence(t_data *big_data, t_list *lst)
{
	if (is_not_redir_and_file(lst) == 1)
	{
		big_data->syntax_error = 1;
		return ;
	}
	if (!big_data->syntax_error)
		check_perm_and_exist(lst);
}

void	check_redir_files(t_data *big_data)
{
	if (is_redir_in_lst(big_data->lst_parsing->first))
		check_file_existence(big_data, big_data->lst_parsing->first);
}
