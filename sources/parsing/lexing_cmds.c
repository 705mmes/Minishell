/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:21:28 by ljerinec          #+#    #+#             */
/*   Updated: 2023/08/31 01:53:25 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_lst_cmds(t_data *big_data)
{
	t_list		*lst_parsing_f;
	t_list		*lst_cmds_f;

	big_data->lst_cmds = create_data_lst();
	lst_parsing_f = big_data->lst_parsing->first;
	lst_cmds_f = big_data->lst_cmds->first;
	setup_lst_cmds(lst_parsing_f, lst_cmds_f);
	define_index_cmds(lst_parsing_f);
	print_lst_cmds(big_data->lst_cmds);
}

char	**array_join(char **array, char *line)
{
	int		i;
	char	**new_array;
	int		len;

	i = 0;
	if (array != NULL)
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
	if (line[ft_strlen(line) - 1] == '\n')
		new_array[i] = ft_substr(line, 0, ft_strlen(line) - 1);
	else
		new_array[i] = ft_strdup(line);
	new_array[++i] = NULL;
	free(array);
	return (new_array);
}

void	setup_lst_cmds(t_data *big_data, t_list *lst)
{
	t_content	*pars_content;
	t_cmds		*cmds_new;
	int			nb_cmds;

	nb_cmds = 0;
	while (lst)
	{
		pars_content = (t_content *)lst->content;
		cmds_new = create_cmds(pars_content->word, pars_content->type);
		while (((t_content *)lst->content)->type != PIPE && lst)
		{
			pars_content = (t_content *)lst->content;
			if (((t_content *)lst->content)->type == CMD)
			{
				((t_cmds *)cmds_new)->cmd = array_join(((t_cmds *)cmds_new)->cmd, pars_content->word);
				lst = lst->next;
				if (lst->next)
				{
					lst = lst->next;
					ft_lstdel_here(&lst, lst->prev);
				}
				else
				{
					ft_lstadd_back(&big_data->lst_cmds->first, ft_lstnew(cmds_new));
					break ;
				}
			}
			else
				lst = lst->next;
		}
		lst = lst->next;
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

void	define_index_cmds(t_list *lst)
{
	t_content	*content;
	int			i;

	i = 0;
	while (lst)
	{
		content = (t_content *)lst->content;
		if (content->type == CMD)
		{
			content->cmd_index = i;
			lst = lst->next;
		}
		else if (content->type == PIPE)
		{
			i++;
			while (content->type == PIPE)
			{
				content->cmd_index = i;
				lst = lst->next;
				content = (t_content *)lst->content;
			}
		}
	}
}

void	print_lst_cmds(t_data_lst *lst_cmds)
{
	t_list	*lst;
	t_cmds	*cmds_content;

	lst = lst_cmds->first;
	while (lst)
	{
		cmds_content = (t_cmds *)lst->content;
		ft_printf("%d\n", cmds_content->type);
		ft_printf("|\n");
		lst = lst->next;
	}
}
