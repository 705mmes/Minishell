/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:31:39 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/05 17:03:09 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_pipes(t_list	*lst)
{
	int			r;
	t_content	*content;

	r = 0;
	while (lst)
	{
		content = (t_content *)lst->content;
		if (content->type == PIPE)
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

void	create_childs(t_data *big_data)
{
	int	nb_childs;
	int	i;

	i = -1;
	nb_childs = ft_count_pipes(big_data->lst_parsing->first) + 1;
	while (++i < nb_childs)
	{
		big_data->childs[i] = fork();
		if (big_data->childs[i] == -1)
			return (perror("Fork failed"));
	}
}


void	feed_childs(t_data *big_data)
{
	t_list		*lst;
	t_content	*content;
	int			u;

	u = 0;
	lst = big_data->lst_parsing->first;
	while (lst)
	{
		content = (t_content *)lst->content;
		if (content->type == CMD)
		{
			get_cmd_path(big_data, content);
			if (pipe(content->fdp) == -1)
				return ((void)perror("Pipe Failed"));
			else
			{	
				exec_child(content, big_data, u);
				u++;
			}
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
