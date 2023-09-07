/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:31:39 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/07 14:46:59 by sammeuss         ###   ########.fr       */
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
	t_list		*lst;
	t_content	*content;
	t_content	*little_bro;
	int			i;

	i = 0;
	lst = big_data->lst_parsing->first;
	pipe_it_up(big_data);
	while (lst && i < ft_count_cmds(big_data) - 1)
	{
		little_bro = (t_content *)lst->content;
		content = (t_content *)lst->content;
		if (content->type == CMD)
		{
			i++;
			little_bro = get_little_bro(big_data);
			printf("big bro coming in\n");
			big_data->big_bro = fork();
			if (big_data->big_bro < 0)
				return (perror("Fork failed"), (void)1);
			else if (big_data->big_bro == 0)
				exec_big_bro(content, little_bro, big_data);
		}
		lst = lst->next;
	}
}

t_content	*get_little_bro(t_data *big_data)
{
	t_list		*lst;
	t_content	*content;
	t_content	*little_bro;
	t_content	*next;

	little_bro = NULL;
	lst = big_data->lst_parsing->first;
	while (lst->next)
	{
		content = (t_content *)lst->content;
		next = (t_content *)lst->next->content;
		if (content->type == CMD && next->type == PIPE)
		{
			content->need_bro = 1;
			little_bro = (t_content *)lst->next->next->content;
		}
		lst = lst->next;
	}
	return (little_bro);
}

void	exec_big_bro(t_content *cmd, t_content *little_bro, t_data *big_data)
{
	printf("%d\n", cmd->need_bro);
	if (dup2(cmd->infile, STDIN_FILENO) == -1
		|| dup2(cmd->outfile, STDOUT_FILENO) == -1)
		return (perror("dup2 failed"), (void)1);
	close(cmd->fdp[0]);
	close(cmd->fdp[1]);
	get_cmd_path(big_data, cmd);
	if (cmd->need_bro == 1)
	{
		big_data->little_bro = fork();
		if (big_data->little_bro < 0)
			return (perror("Fork failed"), (void)1);
		else if (big_data->little_bro == 0)
			exec_little_bro(little_bro, big_data);
	}
	else
		(void)little_bro;
	if (execve(cmd->pathed, cmd->cmd, big_data->env) == -1)
		return (perror("execve error"), (void)1);
}

void	exec_little_bro(t_content *cmd, t_data *big_data)
{
	if (dup2(cmd->infile, STDIN_FILENO) == -1
		|| dup2(cmd->outfile, STDOUT_FILENO) == -1)
		return (perror("dup2 failed"), (void)1);
	close(cmd->fdp[0]);
	close(cmd->fdp[1]);
	get_cmd_path(big_data, cmd);
	waitpid(big_data->big_bro, 0, 0);
	if (execve(cmd->pathed, cmd->cmd, big_data->env) == -1)
		return (perror("execve error"), (void)1);
}
