/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 20:33:33 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/18 18:34:30 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_syntax_checker(t_data *big_data, t_list *lst)
{
	t_content	*content;

	while (lst)
	{
		content = (t_content *)lst->content;
		if (content->type == PIPE && lst->prev == NULL)
		{
			write(2, "minishell: syntax error near unexpected token `",
				ft_strlen("minishell: syntax error near unexpected token `"));
			write(2, content->word, ft_strlen(content->word));
			write(2, "'\n", 2);
			big_data->syntax_error = 1;
			g_mini_sig = 2;
			return ;
		}
		else if (content->type == PIPE && lst->next == NULL)
		{
			ft_printf("minishell:");
			ft_putstr_fd(" syntax error near unexpected token `newline'", 2);
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
