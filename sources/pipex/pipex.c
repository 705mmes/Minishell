/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:31:39 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/20 03:55:06 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_mini_sig;

void	close_all_fd(t_data *big_data)
{
	t_list		*lst;
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

void	close_fd(t_content *content)
{
	if (content->infile > 0)
		close(content->infile);
	if (content->outfile > 2)
		close(content->outfile);
}

void	wait_all_process(t_data *big_data)
{
	t_list		*lst;
	t_content	*content;
	int			exit_code;

	if (!big_data->lst_parsing)
		return ;
	lst = ft_lstlast(big_data->lst_parsing->first);
	content = (t_content *)lst->content;
	while (lst && !is_builtin(content)) //&& content->type == CMD && 
	{
		exit_code = 0;
		waitpid(content->child, &exit_code, 0);
		if (content->exit_code == 0)
		content->exit_code = WEXITSTATUS(exit_code);
		lst = lst->prev;
		if (lst)
			content = (t_content *)lst->content;
	}
}

void	exec_cmd(t_content *content, t_data *big_data)
{
	content->child = fork();
	if (content->child > 0)
		ft_signal_in_fork();
	if (content->child < 0)
	{
		close_all_fd(big_data);
		return (perror("Fork failed"), (void)1);
	}
	else if (content->child == 0 && !content->error && !content->exit_code)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (dup2(content->infile, STDIN_FILENO) == -1
			|| dup2(content->outfile, STDOUT_FILENO) == -1)
			exit(1);
		close_all_fd(big_data);
		get_cmd_path(big_data, content);
		if (execve(content->pathed, content->cmd, big_data->env) == -1)
			exit(127);
	}
	if (content->child == 0)
		exit(1);
}

void	create_childs(t_data *big_data)
{
	t_content	*content;
	t_list		*lst;
	int			exit_code;

	exit_code = 0;
	lst = big_data->lst_parsing->first;
	// print_lst_parsing(big_data->lst_parsing->first);
	remove_pipe(big_data);
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
			else if (ft_strncmp("", content->word, ft_strlen(content->word)))
				exec_cmd(content, big_data);
			close_fd(content);
		}
		lst = lst->next;
	}
	wait_all_process(big_data);
	ft_signal();
}
