/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 23:43:26 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/15 20:29:09 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_mini_sig;

char	**array_dup(char **array)
{
	int		i;
	char	**new_array;

	i = 0;
	while (array[i])
		i++;
	new_array = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (array[++i])
		new_array[i] = ft_strdup(array[i]);
	new_array[i] = NULL;
	return (new_array);
}

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
	big_data->root_path = getenv("HOME");
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

int	is_unmanaged_operator(t_list *lst, t_data *big_data)
{
	t_content	*content;

	if (big_data->syntax_error)
		return (0);
	while (lst)
	{
		content = (t_content *)lst->content;
		if (content->type == OPERATOR)
		{
			printf("minishell: unmanaged operator: `%s'\n", content->word);
			g_mini_sig = 2;
			return (1);
		}
		lst = lst->next;
	}
	return (0);
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
	setup_lst_cmds(big_data->lst_parsing->first);
	ft_list_remove_if(&big_data->lst_parsing->first);
	error_management(big_data);
	ft_list_remove_if(&big_data->lst_parsing->first);
}

t_content	*create_content(char *word, int i)
{
	t_content	*content;

	content = malloc(sizeof(t_content));
	if (!content)
		return (NULL);
	content->word = word;
	content->cmd = NULL;
	content->infile = STDIN_FILENO;
	content->outfile = STDOUT_FILENO;
	content->index = i;
	content->to_delete = 0;
	content->type = NONE;
	content->pathed = NULL;
	content->error = 0;
	content->exit_code = 0;
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
