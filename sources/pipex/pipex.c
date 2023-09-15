/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:31:39 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/15 14:41:02 by ljerinec         ###   ########.fr       */
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
			if (prev->outfile == curr->infile && curr->outfile != next->infile)
				prev->outfile = -1;
			if (prev->outfile != curr->infile && curr->outfile == next->infile)
				next->infile = -1;
		}
		lst = lst->next;
	}
}

void	create_childs(t_data *big_data)
{
	t_content	*content;
	t_list		*lst;

	lst = big_data->lst_parsing->first;
	is_pipe_stuck(big_data);
	while (lst)
	{
		content = (t_content *)lst->content;
		if (content->type == CMD)
		{
			if (is_builtin(content) == 1)
			{
				exec_builtins(content->cmd[0], content, big_data);
				if (content->infile > 0)
					close(content->infile);
				if (content->outfile > 2)
					close(content->outfile);
			}
			else
			{
				content->child = fork();
				if (content->child < 0)
					return (perror("Fork failed"), (void)1);
				else if (content->child == 0 && !content->error)
					exec_child(content, big_data);
				if (content->infile > 0)
					close(content->infile);
				if (content->outfile > 2)
					close(content->outfile);
				waitpid(content->child, 0, 0);
			}
		}
		lst = lst->next;
	}
}

void	exec_child(t_content *cmd, t_data *big_data)
{
	if (dup2(cmd->infile, STDIN_FILENO) == -1
		|| dup2(cmd->outfile, STDOUT_FILENO) == -1)
		exit(1);
	if (cmd->infile > 0)
		close(cmd->infile);
	if (cmd->outfile > 2)
		close(cmd->outfile);
	if (is_builtin(cmd) == 1)
		exit (1);
	get_cmd_path(big_data, cmd);
	if (execve(cmd->pathed, cmd->cmd, big_data->env) == -1)
		exit(1);
}
