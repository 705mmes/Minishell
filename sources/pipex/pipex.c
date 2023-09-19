/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smunio <smunio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:31:39 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/19 18:03:51 by smunio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_mini_sig;

void	remove_pipe(t_data *big_data)
{
	t_list	*lst;

	lst = big_data->lst_parsing->first;
	while (lst)
	{
		if (((t_content *)lst->content)->type == PIPE)
			((t_content *)lst->content)->to_delete = 1;
		lst = lst->next;
	}
	node_to_del(big_data->lst_parsing);
}

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

void	exec_multipipe(t_content *content, t_data *big_data, t_list *lst)
{
	int			exit_code;

	exit_code = 0;
	content->child = fork();
	if (content->child > 0)
	{
		big_data->first_child = content->child; // minishell // ls
		ft_signal_in_fork(); // minishell // ls
	}
	if (content->child < 0)
	{
		close_fd(content);
		return (perror("Fork failed"), (void)1);
	}
	else if (content->child == 0 && !content->error && !content->exit_code)
	{
		printf("Debut du fork %s\n", content->word);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (lst->next)
			exec_multipipe(((t_content *)lst->next->content), big_data, lst->next);
		waitpid(content->child, &exit_code, 0);
		exec_child(content, big_data);
		exit(1);
	}
	close_fd(content); // minishell
	ft_signal();
	content->exit_code = WEXITSTATUS(exit_code);
}

void	create_childs(t_data *big_data)
{
	t_content	*content;
	t_list		*lst;

	lst = big_data->lst_parsing->first;
	is_pipe_stuck(big_data);
	remove_pipe(big_data);
	content = (t_content *)lst->content;
	if (content->type == CMD)
	{
		if (is_builtin(content) == 1)
		{
			if (!content->error)
				exec_builtins(content->cmd[0], content, big_data);
		}
		else
			exec_multipipe(content, big_data, lst);
	}
	waitpid(big_data->first_child, 0, 0);
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
