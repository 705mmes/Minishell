/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:23:51 by ljerinec          #+#    #+#             */
/*   Updated: 2023/08/25 22:57:09 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*setup_data(char **env)
{
	t_data	*big_data;

	(void) env;
	big_data = malloc(sizeof(t_data));
	big_data->read_name = "Minishell >> ";
	big_data->path = ft_split(getenv("PATH"), ':');
	big_data->error = 0;
	big_data->input = NULL;
	big_data->lst_parsing = NULL;
	big_data->lst_cmds = NULL;
	return (big_data);
}

/*
	- Creation de la liste chaine
	- Attribution de chaques mots a sa fonction
	(Commandes, arguments, flag).
*/
void	parsing(t_data *big_data)
{
	// char		**array_split;
	// int			i;

	// i = -1;
	big_data->lst_parsing = create_data_lst();
	ft_split_fou_furieux(big_data->input);
	// while (array_split[++i])
	// 	ft_printf("%s\n", array_split[i]);
	// if (is_some_operators(array_split))
	// 	ft_split_operator(array_split);
}
