/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:38:49 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/16 20:44:48 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_arg(int argc, char **argv)
{
	(void) argv;
	if (argc > 1)
		return (ERROR);
	else
		return (ALL_G);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*big_data;

	if (check_arg(argc, argv) == ERROR)
		return (1);
	big_data = setup_data(env);
	prompt(big_data);
	return (0);
}
