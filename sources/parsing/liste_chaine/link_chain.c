/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_chain.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:11:49 by ljerinec          #+#    #+#             */
/*   Updated: 2023/08/24 12:13:19 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (content->type == PIPE)
			ft_printf("\tPipe");
		else if (content->type == LOGICAL_AND || content->type == BIWISE_OR)
			ft_printf("\tLogical operator");
		else if (content->type == REDIR_I || content->type == REDIR_O)
			ft_printf("\tRedirection");
		else if (content->type == APPEND)
			ft_printf("\tAppend");
		else if (content->type == HEREDOC)
			ft_printf("\tHeredoc");
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

int	is_cmds(t_content *content, t_list *prev)
{
	t_content	*content_prev;

	if (prev)
		content_prev = (t_content *)prev->content;
	if (content->index == 0)
		content->type = CMD;
	else if (prev != NULL && (content_prev->type == PIPE
			|| content_prev->type == FD))
		content->type = CMD;
	if (content->type == CMD)
		return (TRUE);
	return (FALSE);
}

void	define_separator(t_list *lst_parsing)
{
	t_content	*content;
	char		*word;

	while (lst_parsing)
	{
		content = (t_content *)lst_parsing->content;
		word = content->word;
		if (!strncmp(word, "|", ft_strlen(word))
			|| !strncmp(word, "||", ft_strlen(word))
			|| !strncmp(word, "&&", ft_strlen(word)))
			content->type = witch_type(word);
		else if (!strncmp(word, "<", ft_strlen(word))
			|| !strncmp(word, ">", ft_strlen(word))
			|| !strncmp(word, ">>", ft_strlen(word))
			|| !strncmp(word, "<<", ft_strlen(word)))
			content->type = witch_type(word);
		lst_parsing = lst_parsing->next;
	}
}

void	define_word(t_list *lst_parsing)
{
	t_content	*content;

	while (lst_parsing)
	{
		content = (t_content *)lst_parsing->content;
		if (content->type == NONE)
			if (!is_cmds(content, lst_parsing->prev))
				content->type = ARG;
		lst_parsing = lst_parsing->next;
	}
}

void	define_fd(t_list *lst_parsing)
{
	t_content	*content;
	t_content	*next_content;

	while (lst_parsing)
	{
		content = lst_parsing->content;
		if (lst_parsing->next)
		{
			next_content = lst_parsing->next->content;
			if (content->type == REDIR_I || content->type == REDIR_O
				|| content->type == APPEND || content->type == HEREDOC)
				next_content->type = FD;
		}
		else
			return ;
		lst_parsing = lst_parsing->next;
	}
}

void	link_settings(t_data *big_data)
{
	t_list		*lst_parsing;

	lst_parsing = big_data->lst_parsing->first;
	define_separator(lst_parsing);
	define_fd(lst_parsing);
	define_word(lst_parsing);

	env_var_expansion(lst_parsing);
	call_rm_quotes(lst_parsing);
}