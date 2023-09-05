/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_and_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:53:09 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/05 12:06:14 by ljerinec         ###   ########.fr       */
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
			{
				printf("minishell: syntax error near unexpected token 'newline'\n");
				return (1);
			}
			if (((t_content *)lst->next->content)->type != FD)
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

t_list	*find_next_cmd(t_list *lst)
{
	t_content	*content;

	while (lst)
	{
		content = ((t_content *)lst->content);
		if (content->type == CMD)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	check_redir_out(t_list *lst, t_list **current_cmd)
{
	t_content	*content;
	t_content	*content_next;
	int			fd;

	if (!lst || !lst->next)
		return ;
	content = (t_content *)lst->content;
	content_next = (t_content *)lst->next->content;
	fd = open(content_next->word, O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		perror(ft_strjoin("minishell: ", content_next->word));
	if ((*current_cmd))
	{
		if (((t_content *)(*current_cmd)->content)->outfile > 2)
			close(((t_content *)(*current_cmd)->content)->outfile);
		((t_content *)(*current_cmd)->content)->outfile = fd;
	}
	content->to_delete = 1;
	content_next->to_delete = 1;
}

void	check_redir_in(t_list *lst, t_list **current_cmd)
{
	t_content	*content;
	t_content	*content_next;
	int			fd;

	if (!lst || !lst->next)
		return ;
	content = (t_content *)lst->content;
	content_next = (t_content *)lst->next->content;
	fd = open(content_next->word, O_RDONLY);
	if (fd < 0)
		perror(ft_strjoin("minishell: ", content_next->word));
	if ((*current_cmd))
	{
		if (((t_content *)(*current_cmd)->content)->outfile > 2)
			close(((t_content *)(*current_cmd)->content)->infile);
		((t_content *)(*current_cmd)->content)->infile = fd;
	}
	content->to_delete = 1;
	content_next->to_delete = 1;
}

void	check_append(t_list *lst, t_list **current_cmd)
{
	t_content	*content;
	t_content	*content_next;
	int			fd;

	if (!lst || !lst->next)
		return ;
	content = (t_content *)lst->content;
	content_next = (t_content *)lst->next->content;
	fd = open(content_next->word, O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		perror(ft_strjoin("minishell: ", content_next->word));
	if ((*current_cmd))
	{
		if (((t_content *)(*current_cmd)->content)->outfile > 2)
			close(((t_content *)(*current_cmd)->content)->outfile);
		((t_content *)(*current_cmd)->content)->outfile = fd;
	}
	content->to_delete = 1;
	content_next->to_delete = 1;
}

void	check_perm_and_exist(t_list *lst)
{
	t_list		*current_cmd;
	t_content	*content;
	int			flag;

	flag = 0;
	current_cmd = find_next_cmd(lst);
	if (current_cmd == NULL)
		flag = 1;
	while (lst || flag)
	{
		while (lst && ((t_content *)lst->content)->type != PIPE)
		{
			content = ((t_content *)lst->content);
			if (content->type == REDIR_O)
				check_redir_out(lst, &current_cmd);
			else if (content->type == REDIR_I)
				check_redir_in(lst, &current_cmd);
			else if (content->type == APPEND)
				check_append(lst, &current_cmd);
			lst = lst->next;
		}
		while (lst && ((t_content *)lst->content)->type == PIPE)
			lst = lst->next;
		current_cmd = find_next_cmd(lst);
		if (lst == NULL || current_cmd == NULL)
			flag = 0;
	}
}

void	check_file_existence(t_list *lst)
{
	if (is_not_redir_and_file(lst) == 1)
		return ;
	check_perm_and_exist(lst);
}

void	check_redir_files(t_data *big_data)
{
	if (is_redir_in_lst(big_data->lst_parsing->first))
		check_file_existence(big_data->lst_parsing->first);	
}
