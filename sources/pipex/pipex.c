/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:31:39 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/13 13:09:05 by sammeuss         ###   ########.fr       */
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
			if (prev->error != 1 && !prev->error && prev->outfile == 1)
				prev->outfile = curr->fdp[1];
			if (next->error != 1 && !next->error && next->infile == 0)
				next->infile = curr->fdp[0];
		}
		lst = lst->next;
	}
}

void	create_childs(t_data *big_data)
{
	t_content	*content;
	t_list		*lst;

	lst = big_data->lst_parsing->first;
	pipe_it_up(big_data);
	while (lst)
	{
		content = (t_content *)lst->content;
		if (content->type == CMD)
		{
			content->child = fork();
			if (content->child < 0)
				return (perror("Fork failed"), (void)1);
			else if (content->child == 0)
				exec_child(content, big_data, lst);
			if (content->infile > 0)
				close(content->infile);
			if (content->outfile > 2)
				close(content->outfile);
			waitpid(content->child, 0, 0);
		}
		lst = lst->next;
	}
}

void	exec_child(t_content *cmd, t_data *big_data, t_list *lst)
{
	(void)lst;
	if (dup2(cmd->infile, STDIN_FILENO) == -1
		|| dup2(cmd->outfile, STDOUT_FILENO) == -1)
		return ;
	if (cmd->infile > 0)
		close(cmd->infile);
	if (cmd->outfile > 2)
		close(cmd->outfile);
	get_cmd_path(big_data, cmd);
	if (is_builtin(cmd) == 1)
		exec_builtins(cmd->cmd[0], cmd);
	else if (execve(cmd->pathed, cmd->cmd, big_data->env) == -1)
		return ;
}
