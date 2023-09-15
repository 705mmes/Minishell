/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:37:12 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/15 18:10:25 by sammeuss         ###   ########.fr       */
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
	}
}

void	use_prompt(t_data *big_data, char *input)
{
	big_data->input = input;
	add_history(input);
	if (!is_quotes_open(input))
	{
		parsing(big_data);
		if (!big_data->syntax_error)
			exec(big_data);
		big_data->input = NULL;
		if (big_data->syntax_error)
			big_data->syntax_error = 0;
		input = NULL;
		free(input);
	}
}
