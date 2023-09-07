/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 23:43:26 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/07 13:03:01 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*setup_data(char **env)
{
	t_data	*big_data;

	big_data = malloc(sizeof(t_data));
	big_data->read_name = "minishell-1.0$ ";
	big_data->path = ft_split(getenv("PATH"), ':');
	big_data->env = env;
	big_data->syntax_error = 0;
	big_data->input = NULL;
	big_data->lst_parsing = NULL;
	return (big_data);
}

int	ft_arraylen(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

char	**array_join_at_index(char **array, char **a_to_join, int index)
{
	char	**new_array;
	int		i;
	int		u;
	int		j;
	int		size_total;

	i = 0;
	u = 0;
	j = 0;
	if (!a_to_join)
		return (array);
	size_total = ft_arraylen(array) + ft_arraylen(a_to_join);
	new_array = malloc(sizeof(char *) * (size_total + 1));
	while (i < size_total)
	{
		if (i == index)
			while (a_to_join[u])
				new_array[i++] = a_to_join[u++];
		else
			new_array[i++] = array[j];
		j++;
	}
	new_array[i] = NULL;
	return (new_array);
}

void	is_fd_after_separator(t_data *big_data, t_list *lst)
{
	t_content	*content;

	while (lst)
	{
		content = ((t_content *)lst->content);
		if (is_redir(content) || content->type == HEREDOC)
		{
			if (lst->next == 0)
			{
				printf("minishell: syntax error near unexpected token 'newline'\n");
				big_data->syntax_error = 1;
				return ;
			}
			if (((t_content *)lst->next->content)->type != FD)
			{
				printf("minishell: syntax error near unexpected token '%s'\n",
					((t_content *)lst->next->content)->word);
				big_data->syntax_error = 1;
				return ;
			}
		}
		lst = lst->next;
	}
}

void	error_management(t_data *big_data)
{
	t_list	*lst;

	lst = big_data->lst_parsing->first;
	pipe_syntax_checker(big_data, big_data->lst_parsing->first);
	if (!big_data->syntax_error)
		is_fd_after_separator(big_data, lst);
	if (!big_data->syntax_error)
		heredoc_gestion(big_data);
	if (!big_data->syntax_error)
		check_perm_and_exist(lst);
}

/*
	- Creation de la liste chaine
		- Split de l'input sur les whites_spaces()
		- Split du split precedent sur les operateur
	- Attribution de chaques mots a sa fonction via link_settings()
	(Commandes, arguments, flag).
*/
void	parsing(t_data *big_data)
{
	char		**array_split;
	char		**array_fou;
	int			i;

	i = 0;
	big_data->lst_parsing = create_data_lst();
	array_split = ft_split_fou(big_data->input);
	while (array_split[i])
	{
		array_fou = ft_split_keep_char(array_split[i]);
		array_split = array_join_at_index(array_split, array_fou, i);
		i += ft_arraylen(array_fou);
	}
	i = 0;
	while (array_split[i])
	{
		ft_lstadd_back(&big_data->lst_parsing->first,
			ft_lstnew(create_content(array_split[i], i)));
		i++;
	}
	link_settings(big_data);
	setup_lst_cmds(big_data, big_data->lst_parsing->first);
	node_to_delete(big_data->lst_parsing->first);
	error_management(big_data);
	node_to_delete(big_data->lst_parsing->first);
	// if (!big_data->syntax_error)
		// print_lst_parsing(big_data->lst_parsing->first);
}

t_content	*create_content(char *word, int i)
{
	t_content	*content;

	content = malloc(sizeof(t_content));
	if (!content)
		return (NULL);
	content->word = word;
	content->cmd = NULL;
	content->infile = 0;
	content->outfile = 0;
	content->index = i;
	content->to_delete = 0;
	content->type = NONE;
	content->pathed = NULL;
	content->error = 0;
	content->executing = 0;
	return (content);
}

t_data_lst	*create_data_lst(void)
{
	t_data_lst	*new_data_lst;

	new_data_lst = malloc(sizeof(t_data_lst));
	if (!new_data_lst)
		return (NULL);
	new_data_lst->first = NULL;
	new_data_lst->last = NULL;
	new_data_lst->num_link = 0;
	return (new_data_lst);
}
