/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:37:12 by ljerinec          #+#    #+#             */
/*   Updated: 2023/08/28 22:39:05 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(t_data *big_data)
{
	char	*input;

	input = NULL;
	ft_signal();
	while (1)
	{
		input = readline(big_data->read_name);
		if (is_ctrl_d(big_data, input))
			break ;
		else if (strncmp(input, "", ft_strlen(input)) != 0)
			use_prompt(big_data, input);
		big_data->read_name = "Minishell-1.0$ ";
	}
}

void	use_prompt(t_data *big_data, char *input)
{
	big_data->input = input;
	add_history(input);
	if (!is_quotes_open(input))
	{
		parsing(big_data);
		print_lst_parsing(big_data->lst_parsing->first);
		big_data->input = NULL;
		// free_chainlink(big_data->lst_parsing);
		input = NULL;
		free(input);
	}
}
