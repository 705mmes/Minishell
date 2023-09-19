/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:31:39 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/19 22:15:04 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_mini_sig;

void	close_fd(t_data *big_data)
{
	t_list	*lst;
	t_content	*content;

	lst = big_data->lst_parsing->first;
	while (lst)
	{
		content = (t_content *)lst->content;
		if (content->infile > 0)
			close(content->infile);
		if (content->outfile > 2)
			close(content->outfile);
		lst = lst->next;
	}
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

void	exec_multipipe(t_content *content, t_data *big_data)
{
	content->child = fork();
	if (content->child > 0)
		ft_signal_in_fork();
	if (content->child < 0)
	{
		close_fd(big_data);
		return (perror("Fork failed"), (void)1);
	}
	else if (content->child == 0 && !content->error && !content->exit_code)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		exec_child(content, big_data);
		exit(1);
	}
}

void	create_childs(t_data *big_data)
{
	t_content	*content;
	t_list		*lst;
	int			exit_code;

	exit_code = 0;
	lst = big_data->lst_parsing->first;
	is_pipe_stuck(big_data);
	while (lst)
	{
		content = (t_content *)lst->content;
		if (content->type == CMD)
		{
			if (is_builtin(content) == 1)
			{
				if (!content->error)
					exec_builtins(content->cmd[0], content, big_data);
			}
			else
				exec_multipipe(content, big_data);
		}
		lst = lst->next;
	}
	lst = big_data->lst_parsing->first;
	while (lst)
	{
		content = (t_content *)lst->content;
		waitpid(content->child, &exit_code, 0);
		if (content->infile > 0)
			close(content->infile);
		if (content->outfile > 2)
			close(content->outfile);
		content->exit_code = WEXITSTATUS(exit_code);
		lst = lst->next;
	}
	ft_signal();
}

void	exec_child(t_content *cmd, t_data *big_data)
{
	if (dup2(cmd->infile, STDIN_FILENO) == -1
		|| dup2(cmd->outfile, STDOUT_FILENO) == -1)
		exit(1);
	close_fd(big_data);
	get_cmd_path(big_data, cmd);
	if (execve(cmd->pathed, cmd->cmd, big_data->env) == -1)
		exit(127);
}