/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:57:01 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/05 15:18:50 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmdve	*setup_cmd(t_p_data *data, char **cmd)
{
	int		i;
	int		u;
	t_cmdve	*r;

	i = -1;
	u = 0;
	r = malloc(sizeof(t_cmdve));
	while (++u < array_len(cmd))
		r->args = ft_strjoin(r->args, cmd[u]);
	while (data->path[++i])
	{
		r->cmd_path = ft_strjoin(data->path[i], "/");
		r->cmd_path = ft_strjoin(r->cmd_path, cmd[0]);
		if (access(r->cmd_path, F_OK | X_OK) == 0)
			break ;
	}
	return (r);
}

void	ft_second_child(t_p_data *data)
{
	t_cmdve	*cmd_2;

	if (dup2(data->fd[0], STDIN_FILENO) == -1
		|| dup2(data->outfile, STDOUT_FILENO) == -1)
		perror("dup2 failed child2");
	close(data->fd[1]);
	close(data->fd[0]);
	waitpid(data->child1, 0, 0);
	cmd_2 = setup_cmd(data, data->cmd2);
	if (execve(cmd_2->cmd_path, data->cmd2, data->env) == -1)
	{
		perror("execve error child1");
		exit(1);
	}
}

void	ft_first_child(t_p_data *data)
{
	t_cmdve	*cmd_1;

	if (dup2(data->infile, STDIN_FILENO) == -1
		|| dup2(data->fd[1], STDOUT_FILENO) == -1)
		perror("dup2 failed child1");
	close(data->fd[0]);
	close(data->fd[1]);
	cmd_1 = setup_cmd(data, data->cmd1);
	if (execve(cmd_1->cmd_path, data->cmd1, data->env) == -1)
	{
		perror("execve error child1");
		exit(1);
	}
}
