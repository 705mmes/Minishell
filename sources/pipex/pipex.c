/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:31:39 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/11 16:51:38 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
				prev = (t_content *)lst->prev->content;
			if (lst->next)
				next = (t_content *)lst->next->content;
			if (pipe(((t_content *)lst->content)->fdp) == -1)
				return ((void)perror("Pipe Failed"));
			if (prev->error != 1)
				prev->outfile = curr->fdp[0];
			if (next->error != 1)
				next->infile = curr->fdp[1];
		}
		lst = lst->next;
	}
}

void	create_childs(t_data *big_data)
{
	t_content	*content;
	t_list		*lst;

	lst = big_data->lst_parsing->first;
	content = (t_content *)big_data->lst_parsing->first->content;
	pipe_it_up(big_data);
	if (content->type == CMD)
	{
		content->im_first = 1;
		printf("big bro coming in\n");
		content->child = fork();
		if (content->child < 0)
			return (perror("Fork failed"), (void)1);
		else if (content->child == 0)
			exec_child(content, big_data, lst);
	}
	waitpid(content->child, 0, 0);
}

void	exec_child(t_content *cmd, t_data *big_data, t_list *lst)
{
	if (dup2(cmd->infile, STDIN_FILENO) == -1
		|| dup2(cmd->outfile, STDOUT_FILENO) == -1)
		return (perror("dup2 failed"), (void)1);
	close(cmd->fdp[0]);
	close(cmd->fdp[1]);
	get_cmd_path(big_data, cmd);
	if (lst->next && ((t_content *)lst->next->content)->type == PIPE)
	{
		((t_content *)lst->next->next->content)->child = fork();
		if (((t_content *)lst->next->next->content)->child < 0)
			return (perror("Fork failed"), (void)1);
		else if (((t_content *)lst->next->next->content)->child == 0)
			exec_child((t_content *)lst->next->next->content, big_data, lst->next->next);
	}
	if (cmd->im_first != 1)
		waitpid(((t_content *)lst->prev->prev->content)->child, 0, 0);
	if (execve(cmd->pathed, cmd->cmd, big_data->env) == -1)
		return (perror("execve error"), (void)1);
}
