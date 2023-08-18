/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:23:51 by ljerinec          #+#    #+#             */
/*   Updated: 2023/08/18 13:25:38 by ljerinec         ###   ########.fr       */
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
	char		**array_split;
	int			i;

	i = 0;
	big_data->lst_parsing = create_data_lst();
	if (is_quoted(big_data->input))
		array_split = ft_split_fou(big_data->input);
	else
		array_split = ft_split(big_data->input, ' ');
	while (array_split[i])
	{
		ft_lstadd_back(&big_data->lst_parsing->first,
			ft_lstnew(create_content(array_split[i], i)));
		i++;
	}
	link_settings(big_data);
}

t_content	*create_content(char *word, int i)
{
	t_content	*content;

	content = malloc(sizeof(t_content));
	content->word = word;
	content->index = i;
	content->type = NONE;
	content->is_expand = 0;
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
		if (content->type == OPERATOR)
			ft_printf("\tSeparator");
		else if (content->type == REDIR)
			ft_printf("\tRedirection");
		else if (content->type == FLAG)
			ft_printf("\tFlag");
		else if (content->type == CMD)
			ft_printf("\tCmd");
		else if (content->type == ARG)
			ft_printf("\tArg");
		else if (content->type == FD)
			ft_printf("\tFd");
		ft_printf("\n");
		lst_parsing = lst_parsing->next;
	}
}
