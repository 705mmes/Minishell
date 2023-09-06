/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:31:39 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/06 18:19:32 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_cmds(t_list	*lst)
{
	int			r;
	t_content	*content;

	r = 0;
	while (lst)
	{
		content = (t_content *)lst->content;
		if (content->type == CMD)
			r++;
		lst = lst->next;
	}
	return (r);
}

void	get_cmd_path(t_data *big_data, t_content *content)
{
	int	i;

	i = -1;
	while (big_data->path[++i])
	{
		content->pathed = ft_strjoin(big_data->path[i], "/");
		content->pathed = ft_strjoin(content->pathed, content->cmd[0]);
		if (access(content->pathed, X_OK) == 0)
			break ;
	}
}

void	pipe_it_up(t_data *big_data)
{
	t_list		*lst;
	t_content	*prev;
	t_content	*next;
	t_content	*curr;

	lst = big_data->lst_parsing->first;
	prev = NULL;
	next = NULL;
	while (lst)
	{
		curr = (t_content *)lst->content;
		if (((t_content *)lst->content)->type == PIPE)
		{
			if (lst->prev)
				prev = (t_content *)lst->prev->content;
			if (lst->next)
				next = (t_content *)lst->next->content;
			if (pipe(((t_content *)lst->content)->fdp) == -1)
				return ((void)perror("Pipe Failed"));
			prev->infile = curr->fdp[0];
			next->outfile = curr->fdp[1];
		}
		lst = lst->next;
	}
}

void	create_childs(t_data *big_data)
{
	t_list		*lst;
	t_content	*content;
	int			nb_childs;
	int			i;

	i = 0;
	lst = big_data->lst_parsing->first;
	nb_childs = ft_count_cmds(big_data->lst_parsing->first) + 1;
	big_data->childs = malloc(sizeof(pid_t) * nb_childs);
	if (!big_data->childs)
		return (perror("Malloc error"), (void)1);
	pipe_it_up(big_data);
	while (lst)
	{
		content = (t_content *)lst->content;
		if (content->type == CMD)
		{
			get_cmd_path(big_data, content);
			i++;
		}
		lst = lst->next;
	}
}

void	exec_child(t_content *content, t_data *big_data, int index)
{
	if (dup2(content->infile, STDIN_FILENO) == -1
		|| dup2(content->outfile, STDOUT_FILENO) == -1)
		return (perror("dup2 failed"), (void)1);
	close(content->fdp[0]);
	close(content->fdp[1]);
	if (index > 0)
		waitpid(big_data->childs[index - 1], 0, 0);
	if (execve(content->pathed, content->cmd, big_data->env) == -1)
	{
		perror("execve error child1");
		exit(1);
	}
}
