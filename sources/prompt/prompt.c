/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:37:12 by ljerinec          #+#    #+#             */
/*   Updated: 2023/07/18 16:46:15 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(t_data *big_data)
{
	char	*input;

	ft_signal();
	while (1)
	{
		input = readline("Minishell >> ");
		if (ft_strncmp(input, "", ft_strlen(input)) != 0)
		{
			add_history(input);
			big_data->input = input;
			// parsing(big_data);
			ft_printf(" minishell: %s: command not found\n", big_data->input);
		}
		if (input == NULL)
		{
			printf(" exit\n");
			break ;
		}
		free(input);
	}
}
