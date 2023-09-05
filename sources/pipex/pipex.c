/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:31:39 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/05 15:16:43 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipex(t_p_data *data)
{
	if (pipe(data->fd) == -1)
		return ((void)perror("Pipe Failed"));
	data->child1 = fork();
	if (data->child1 < 0)
		return (perror("Fork Failed1"));
	else if (data->child1 == 0)
		ft_first_child(data);
	else if (data->child1 > 0)
		data->child2 = fork();
	if (data->child2 < 0)
		return (perror("Fork Failed2"));
	if (data->child2 == 0)
		ft_second_child(data);
}

int	pipex_main(int ac, char **av, char **env)
{
	t_p_data	*data;

	if (ac != 5)
		return (perror("run ./pipex file1 cmd1 cmd2 file2"), 1);
	data = quick_setup(av, env);
	pipex(data);
	return (0);
}
