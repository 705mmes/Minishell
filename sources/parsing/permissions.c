/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permissions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 20:19:31 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/20 01:43:54 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	checking_fd(int fd, t_list **current_cmd, t_content *content_next)
{
	char	*msg_error;

	msg_error = ft_strjoin(ft_strdup("minishell: "), content_next->word);
	if (fd < 0)
	{
		((t_content *)(*current_cmd)->content)->error = 1;
		perror(msg_error);
		free(msg_error);
		if (((t_content *)(*current_cmd)->content)->exit_code == 0)
			((t_content *)(*current_cmd)->content)->exit_code = 1;
	}
}

void	check_redir_out(t_list *lst, t_list **current_cmd)
{
	t_content	*content;
	t_content	*content_next;
	int			fd;

	fd = 0;
	if (!lst || !lst->next)
		return ;
	content = (t_content *)lst->content;
	content_next = (t_content *)lst->next->content;
	if (((t_content *)(*current_cmd)->content)->error == 0)
		fd = open(content_next->word, O_CREAT
				| O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	checking_fd(fd, current_cmd, content_next);
	if ((*current_cmd) && fd > 0)
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

	fd = 0;
	if (!lst || !lst->next)
		return ;
	content = (t_content *)lst->content;
	content_next = (t_content *)lst->next->content;
	if (((t_content *)(*current_cmd)->content)->error == 0)
		fd = open(content_next->word, O_RDONLY);
	checking_fd(fd, current_cmd, content_next);
	if ((*current_cmd) && fd > 0)
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

	fd = 0;
	if (!lst || !lst->next)
		return ;
	content = (t_content *)lst->content;
	content_next = (t_content *)lst->next->content;
	if (((t_content *)(*current_cmd)->content)->error == 0)
		fd = open(content_next->word, O_CREAT | O_APPEND
				| O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	checking_fd(fd, current_cmd, content_next);
	if ((*current_cmd) && fd > 0)
	{
		if (((t_content *)(*current_cmd)->content)->outfile > 2)
			close(((t_content *)(*current_cmd)->content)->outfile);
		((t_content *)(*current_cmd)->content)->outfile = fd;
	}
	content->to_delete = 1;
	content_next->to_delete = 1;
}
