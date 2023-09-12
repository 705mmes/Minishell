/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:38:49 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/12 12:01:50 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_data *big_data, char **env, char *cmd);
void	test(t_data *big_data);

int	main(int argc, char **argv, char **env)
{
	t_data	*big_data;

	if (check_arg(argc, argv) == ERROR)
		return (freeall(NULL, ERROR));
	big_data = setup_data(env);
	prompt(big_data);
	return (0);
}
