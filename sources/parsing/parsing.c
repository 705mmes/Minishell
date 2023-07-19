/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:23:51 by ljerinec          #+#    #+#             */
/*   Updated: 2023/07/20 01:32:03 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*setup_data(char **env)
{
	t_data	*big_data;

	(void) env;
	big_data = malloc(sizeof(t_data));
	big_data->read_name = "Minishell >> ";
	big_data->path = getenv("PATH");
	big_data->error = 0;
	big_data->input = NULL;
	big_data->quotes_open = 0;
	big_data->lst_parsing = NULL;
	big_data->lst_cmds = NULL;
	return (big_data);
}

void	parsing(t_data *big_data)
{
	char		**array_split;
	int			i;

	i = 0;
	big_data->lst_parsing = create_data_lst();
	array_split = ft_split(big_data->input, ' ');
	while (array_split[i])
	{
		ft_lstadd_back(&big_data->lst_parsing->first,
			ft_lstnew(create_content(array_split[i])));
		i++;
	}
	link_settings(big_data);
}

t_content	*create_content(char *word)
{
	t_content	*content;

	content = malloc(sizeof(t_content));
	content->word = word;
	content->is_arg = 0;
	content->is_cmds = 0;
	content->is_pipe = 0;
	content->is_redir = 0;
	content->is_semicolon = 0;
	return (content);
}

t_data_lst	*create_data_lst(void)
{
	t_data_lst	*new_data_lst;

	new_data_lst = malloc(sizeof(t_data_lst));
	new_data_lst->first = NULL;
	new_data_lst->last = NULL;
	new_data_lst->num_link = 0;
	return (new_data_lst);
}

void	print_lst_parsing(t_list *lst_parsing)
{
	t_content	*content;

	if (!lst_parsing)
		return ;
	while (lst_parsing)
	{
		content = (t_content *)lst_parsing->content;
		ft_printf("%s ", content->word);
		if (content->is_pipe)
			ft_printf("is a pipe");
		else if (content->is_redir)
			ft_printf("is a redirection");
		else if (content->is_arg)
			ft_printf("is a arguments of cmd");
		ft_printf("\n");
		lst_parsing = lst_parsing->next;
	}
}
