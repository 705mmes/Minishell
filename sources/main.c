/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:38:49 by ljerinec          #+#    #+#             */
/*   Updated: 2023/08/17 10:23:41 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_data *big_data, char **env, char *cmd);

int	main(int argc, char **argv, char **env)
{
	// (void) argc;
	// (void) argv;
	// (void) env;
	t_data	*big_data;

	if (check_arg(argc, argv) == ERROR)
		return (freeall(NULL, ERROR));
	big_data = setup_data(env);
	// exec_cmd(big_data, env, "ls");
	prompt(big_data);
	// ft_printf("%d\n", is_quoted_and_who("ec'ho test", 2));
	return (0);
}

void	exec_cmd(t_data *big_data, char **env, char *cmd)
{
	int		i;
	char	*pathed;
	pid_t	exec_process;

	i = -1;
	while (big_data->path[++i])
	{
		pathed = ft_strjoin(big_data->path[i], "/");
		pathed = ft_strjoin(pathed, cmd);
		if (access(pathed, X_OK) == 0)
			break ;
	}
	char *argv[] = {"", "-la", (char *) NULL };
	exec_process = fork();
	if (exec_process == 0)
		execve(pathed, argv, env);
	else
		waitpid(exec_process, 0, 0);
}
