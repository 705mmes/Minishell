/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:21:28 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/16 15:16:26 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// liens entre prev et next a refaire
t_list	*ft_remove_trash(t_list *lst, t_list *to_delete)
{
	while (lst)
	{
		if (lst == to_delete)
		{
			if (lst->prev)
				lst->prev = lst;
			if (lst->next)
				lst->next = lst->next->next;
			lst = lst->next;
			free(lst->prev)
		}
	}
}

void	ft_check_for_trash(t_list *lst)
{
	t_list		*index;
	t_content	*content;

	index = lst;
	while (index)
	{
		content = (t_content *)index->content;
		if (content->to_delete == 1)
			index = ft_remove_trash(lst, index);
	}
}

void	create_lst_cmds(t_data *big_data)
{
	heredoc_gestion(big_data);
	setup_lst_cmds(big_data->lst_parsing->first);
	ft_check_for_trash(big_data->lst_parsing->first);
	check_redir_files(big_data);
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
	if (array)
		free(array);
	return (new_array);
}

void	ft_print_tab(char **array)
{
	int	i;

	i = -1;
	if (!array)
	{
		printf("(NULL)\n");
		return ;
	}
	while (array[++i])
		printf("%s\n", array[i]);
}

void	setup_lst_cmds(t_list *lst)
{
	t_content	*content;
	t_list		*save;

	save = NULL;
	while (lst)
	{
		if (lst)
			content = (t_content *)lst->content;
		while (lst && ((t_content *)lst->content)->type != PIPE)
		{
			content = (t_content *)lst->content;
			if (content->type == CMD)
			{
				if (save != NULL)
					content->to_delete = 1;
				else
					save = lst;
				((t_content *)save->content)->cmd = array_join(((t_content *)save->content)->cmd, content->word);
				if (lst == NULL)
					break ;
			}
			lst = lst->next;
		}
		if (lst)
			content = (t_content *)lst->content;
		if (lst && content->type == PIPE)
		{
			lst = lst->next;
			save = NULL;
		}
	}
}
