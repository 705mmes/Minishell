/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_gestion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:13:52 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/11 15:52:27 by ljerinec         ###   ########.fr       */
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

void	heredoc_read(t_list *lst, int i)
{
	t_content	*c_next;
	char		*input;
	char		*file_name;
	int			fd;

	c_next = (t_content *)lst->next->content;
	file_name = ft_strjoin(".heredoc_", ft_itoa(i));
	fd = open(file_name, O_CREAT | O_APPEND | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	input = NULL;
	while (1)
	{
		input = readline("> ");
		if (input == NULL)
			break ;
		if (ft_strncmp(c_next->word, input, ft_strlen(input)) == 0)
			break ;
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
	}
	c_next->word = file_name;
	close(fd);
}

void	do_heredoc_things(t_list *lst)
{
	t_content	*content;
	t_content	*content_next;
	int			i;

	i = 0;
	while (lst)
	{
		if (!lst->next)
			return;
		content = (t_content *)lst->content;
		content_next = (t_content *)lst->next->content;
		if (content->type == HEREDOC && content_next->type == FD)
			heredoc_read(lst, i++);
		lst = lst->next;
	}
}

void	heredoc_gestion(t_data *big_data)
{
	t_list	*lst;

	lst = big_data->lst_parsing->first;
	if (!is_heredoc_in_lst(lst))
		return ;
	// if (!is_not_delimitor_after_heredoc(lst))
	do_heredoc_things(lst);
}
