/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:37:12 by ljerinec          #+#    #+#             */
/*   Updated: 2023/07/20 15:50:09 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quotes_open(char *input)
{
	int	i;
	int	state;
	// int	flag;

	i = 0;
	state = 0;
	// flags = 0;
	while (input[i] && input)
	{
		if (state == 0 && (input[i] == 39 || input[i] == 34))
			state = input[i++];
		if (input[i] == state)
			state = 0;
		i++;
	}
	if (state > 0)
		return (TRUE);
	return (FALSE);
}

int	is_ctrl_d(t_data *big_data, char *input)
{
	if (input == NULL)
	{
		ft_printf(" exit\n");
		big_data->input = NULL;
		return (TRUE);
	}
	return (FALSE);
}

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
		else if (strncmp(input, "", ft_strlen(input)) != 0 && !is_quotes_open(input))
		{
			big_data->input = input;
			add_history(input);
			printf("%s\n", big_data->input);
			// parsing(big_data);
			// print_lst_parsing(big_data->lst_parsing->first);
			big_data->input = NULL;
			free(input);
		}
		big_data->read_name = "Minishell >> ";
	}
}
