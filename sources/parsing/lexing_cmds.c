/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:21:28 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/01 18:29:00 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_to_delete(t_list *lst)
{}

void	create_lst_cmds(t_data *big_data)
{
	// t_list		*lst_parsing_f;
	// t_list		*lst_cmds_f;

	big_data->lst_cmds = create_data_lst();
	// lst_parsing_f = big_data->lst_parsing->first;
	// lst_cmds_f = big_data->lst_cmds->first;
	setup_lst_cmds(big_data, big_data->lst_parsing->first);
	delete_to_delete(big_data->lst_parsing->first);
	print_lst_cmds(big_data->lst_cmds);
}

char	**array_join(char **array, char *line)
{
	int		i;
	char	**new_array;
	int		len;

	i = 0;
	if (!array)
		i = 0;
	else
		while (array[i])
			i++;
	len = i;
	new_array = malloc(sizeof(char *) * (i + 2));
	if (!new_array)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_array[i] = array[i];
		i++;
	}
	new_array[i] = line;
	new_array[++i] = NULL;
	free(array);
	return (new_array);
}

void	ft_print_tab(char **array)
{
	int	i;

	i = -1;
	if (!array)
	{
		printf("array[0] = (NULL)\n");
		return ;
	}
	while (array[++i])
		printf("array[%d] = %s\n", i, array[i]);
}

void	setup_lst_cmds(t_data *big_data, t_list *lst)
{
	t_cmds		*cmds_new;
	t_cmds		*cmds_pipe;

	while (lst)
	{
		cmds_new = create_cmds(NULL, ((t_content *)lst->content)->type);
		while (lst && ((t_content *)lst->content)->type != PIPE)
		{
			if (((t_content *)lst->content)->type == CMD)
			{
				if (((t_cmds *)cmds_new)->cmd != NULL)
					((t_content *)lst->content)->to_delete = 1;
				((t_cmds *)cmds_new)->cmd = array_join(((t_cmds *)cmds_new)->cmd, ((t_content *)lst->content)->word);
				if (lst)
					lst = lst->next;
				if (lst == NULL)
				{
					ft_lstadd_back(&big_data->lst_cmds->first, ft_lstnew(cmds_new));
					break ;
				}
			}
			else if (lst)
			{
				lst = lst->next;
				if (lst == NULL)
					ft_lstadd_back(&big_data->lst_cmds->first, ft_lstnew(cmds_new));
			}
		}
		if (lst && ((t_content *)lst->content)->type == PIPE)
		{
			if (cmds_new->type == CMD)
				ft_lstadd_back(&big_data->lst_cmds->first, ft_lstnew(cmds_new));
			cmds_pipe = create_cmds(NULL, ((t_content *)lst->content)->type);
			ft_lstadd_back(&big_data->lst_cmds->first, ft_lstnew(cmds_pipe));
			lst = lst->next;
		}
	}
}

t_cmds	*create_cmds(char *word, t_type type)
{
	t_cmds	*cmds;

	cmds = malloc(sizeof(t_cmds));
	if (!cmds)
		return (NULL);
	cmds->type = type;
	cmds->cmd = array_join(NULL, word);
	cmds->infile = -1;
	cmds->outfile = -1;
	return (cmds);
}

void	print_lst_cmds(t_data_lst *lst_cmds)
{
	t_list	*lst;
	t_cmds	*cmds_content;

	lst = lst_cmds->first;
	while (lst)
	{
		cmds_content = (t_cmds *)lst->content;
		if (cmds_content->type == CMD)
			ft_print_tab(cmds_content->cmd);
		else if (cmds_content->type == PIPE)
			ft_printf("|\n");
		lst = lst->next;
	}
}
