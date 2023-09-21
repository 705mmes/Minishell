/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 20:33:33 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/21 15:59:11 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_pipe(t_data *big_data)
{
	t_list	*lst;

	lst = big_data->lst_parsing->first;
	while (lst)
	{
		if (((t_content *)lst->content)->type == PIPE)
			((t_content *)lst->content)->to_delete = 1;
		lst = lst->next;
	}
	node_to_del(big_data->lst_parsing);
}

t_content	*find_prev(t_list *lst)
{
	t_content	*content;

	content = NULL;
	while (lst)
	{
		content = ((t_content *)lst->content);
		if (content->type == CMD)
			break ;
		lst = lst->prev;
	}
	return (content);
}

void	pipe_syntax_checker(t_data *big_data, t_list *lst)
{
	t_content	*content;

	while (lst)
	{
		content = (t_content *)lst->content;
		if ((content->type == PIPE && lst->prev == NULL)
			|| (content->type == PIPE && lst->next
				&& ((t_content*)lst->next->content)->type == PIPE))
		{
			msg_e("minishell: syntax error near unexpected token `",
				content->word, "`\n");
			big_data->syntax_error = 1;
			g_mini_sig = 2;
			return ;
		}
		else if (content->type == PIPE && lst->next == NULL)
		{
			msg_e("minishell: syntax error near unexpected token `newline'\n",
				NULL, NULL);
			big_data->syntax_error = 1;
			g_mini_sig = 2;
			return ;
		}
		lst = lst->next;
	}
}

void	pipe_it_up(t_data *big_data)
{
	t_list		*lst;
	t_content	*prev;
	t_content	*next;
	t_content	*curr;

	lst = big_data->lst_parsing->first;
	while (lst)
	{
		curr = (t_content *)lst->content;
		if (curr->type == PIPE)
		{
			if (lst->prev)
				prev = find_prev(lst);
			if (lst->next)
				next = (t_content *)lst->next->content;
			if (pipe(((t_content *)lst->content)->fdp) == -1)
				return ((void)perror("Pipe Failed"));
			prev->outfile = curr->fdp[1];
			curr->infile = curr->fdp[1];
			next->infile = curr->fdp[0];
			curr->outfile = curr->fdp[0];
		}
		lst = lst->next;
	}
}

void	is_pipe_stuck(t_data *big_data)
{
	t_list		*lst;
	t_content	*prev;
	t_content	*next;
	t_content	*curr;

	lst = big_data->lst_parsing->first;
	while (lst)
	{
		if (!lst->next && !lst->prev)
			break ;
		curr = (t_content *)lst->content;
		if (curr->type == PIPE)
		{
			prev = (t_content *)lst->prev->content;
			next = (t_content *)lst->next->content;
			if ((prev->outfile == curr->infile
					&& curr->outfile != next->infile))
				prev->outfile = -1;
			if ((prev->outfile != curr->infile
					&& curr->outfile == next->infile))
				next->infile = -1;
		}
		lst = lst->next;
	}
}
