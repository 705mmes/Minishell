/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 23:43:26 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/16 21:38:04 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_mini_sig;

t_data	*setup_data(char **env)
{
	t_data	*big_data;

	big_data = malloc(sizeof(t_data));
	big_data->read_name = "minishell-1.0$ ";
	big_data->path = ft_split(getenv("PATH"), ':');
	big_data->env = array_dup(env);
	big_data->syntax_error = 0;
	big_data->input = NULL;
	big_data->lst_parsing = NULL;
	big_data->root_path = ft_getenv(big_data, "HOME");
	return (big_data);
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
	free(array);
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
				ft_putstr_fd("minishell: syntax error near unexpected token `newline'", 2);
				big_data->syntax_error = 1;
				g_mini_sig = 2;
				return ;
			}
			if (((t_content *)lst->next->content)->type != FD)
			{
				write(2, "minishell: syntax error near unexpected token `", ft_strlen("minishell: syntax error near unexpected token `"));
				write(2, ((t_content *)lst->next->content)->word, ft_strlen(((t_content *)lst->next->content)->word));
				write(2, "'\n", 2);
				big_data->syntax_error = 1;
				g_mini_sig = 2;
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
	if (is_unmanaged_operator(big_data->lst_parsing->first, big_data))
		big_data->syntax_error = 1;
	if (!big_data->syntax_error)
		is_fd_after_separator(big_data, lst);
	if (!big_data->syntax_error)
		heredoc_gestion(big_data);
	if (!big_data->syntax_error)
		pipe_it_up(big_data);
	if (!big_data->syntax_error)
		check_perm_and_exist(lst);
}

void	create_link_chained(t_data *big_data)
{
	char		**array_split;
	char		**array_fou;
	int			i;

	i = 0;
	array_split = ft_split_fou(big_data->input);
	while (array_split[i])
	{
		array_fou = ft_split_keep_char(array_split[i]);
		array_split = array_join_at_index(array_split, array_fou, i);
		i += ft_arraylen(array_fou);
		free(array_fou);
	}
	i = 0;
	while (array_split[i])
	{
		ft_lstadd_back(&big_data->lst_parsing->first,
			ft_lstnew(create_content(array_split[i], i)));
		i++;
	}
}

void	parsing(t_data *big_data)
{
	big_data->lst_parsing = create_data_lst();
	create_link_chained(big_data);
	link_settings(big_data);
	setup_lst_cmds(big_data->lst_parsing->first);
	ft_check_for_trash(big_data->lst_parsing->first);
	error_management(big_data);
	ft_check_for_trash(big_data->lst_parsing->first);
}
