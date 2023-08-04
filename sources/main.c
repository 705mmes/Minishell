/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:38:49 by ljerinec          #+#    #+#             */
/*   Updated: 2023/08/04 03:37:18 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_data *big_data, char **env, char *cmd);

int	main(int argc, char **argv, char **env)
{
	t_data	*big_data;

	if (check_arg(argc, argv) == ERROR)
		return (freeall(NULL, ERROR));
	big_data = setup_data(env);
	prompt(big_data);
	// exec_cmd(big_data, env, "ls");
	return (0);
}

void	exec_cmd(t_data *big_data, char **env, char *cmd)
{
	int		i;
	char	*pathed;

	i = -1;
	while (big_data->path[++i])
	{
		pathed = ft_strjoin(big_data->path[i], "/");
		pathed = ft_strjoin(pathed, cmd);
		if (access(pathed, X_OK) == 0)
			break ;
	}
	char * argv[] = {"-la", (char *) NULL };
	execve(pathed, argv, env);
}
