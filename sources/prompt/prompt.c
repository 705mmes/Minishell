/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:37:12 by ljerinec          #+#    #+#             */
/*   Updated: 2023/07/19 16:36:31 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(t_data *big_data)
{
	char	*input;

	ft_signal();
	while (1)
	{
		big_data->input = readline("Minishell >> ");
		input = big_data->input;
		if (ft_strncmp(input, "", ft_strlen(input)) != 0)
		{
			add_history(input);
			parsing(big_data);
			// create_cmds(big_data);
			print_lst_parsing(big_data->lst_parsing->first);
		}
		if (input == NULL)
		{
			ft_printf(" exit\n");
			big_data->input = NULL;
			break ;
		}
		free(input);
	}
}
