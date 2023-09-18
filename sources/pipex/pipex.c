/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:31:39 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/18 16:48:23 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_mini_sig;

void	close_fd(t_content *content)
{
	if (content->infile > 0)
		close(content->infile);
	if (content->outfile > 2)
		close(content->outfile);
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
	int			exit_code;

	exit_code = 0;
	content->child = fork();
	ft_signal_in_fork();
	if (content->child < 0)
		return (perror("Fork failed"), (void)1);
	else if (content->child == 0 && !content->error && !content->exit_code)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		exec_child(content, big_data);
		exit(1);
	}
	if (content->child == 0)
		exit(1);
	waitpid(content->child, &exit_code, 0);
	content->exit_code = WEXITSTATUS(exit_code);
	ft_signal();
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
				if (!content->error)
					exec_builtins(content->cmd[0], content, big_data);
			}
			else
				exec_multipipe(content, big_data);
			close_fd(content);
		}
		lst = lst->next;
	}
}

void	exec_child(t_content *cmd, t_data *big_data)
{
	if (dup2(cmd->infile, STDIN_FILENO) == -1
		|| dup2(cmd->outfile, STDOUT_FILENO) == -1)
		exit(1);
	close_fd(cmd);
	get_cmd_path(big_data, cmd);
	if (execve(cmd->pathed, cmd->cmd, big_data->env) == -1)
		exit(127);
}
