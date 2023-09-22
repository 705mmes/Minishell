/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:22:43 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/22 15:09:21 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quoted(char *input)
{
	int	i;

	i = -1;
	if (!input)
		return (0);
	while (input[++i])
		if (input[i] == 39 || input[i] == '"')
			return (1);
	return (0);
}

char	*ft_strjoin_char(char *s1, char s2)
{
	size_t	sizetotal;
	char	*chainjoin;
	int		i;

	i = 0;
	sizetotal = ft_strlen(s1) + 1;
	chainjoin = malloc(sizeof(char) * (sizetotal + 1));
	if (!chainjoin)
		return (NULL);
	if (s1)
	{
		while (i < ft_strlen_gnl(s1))
		{
			chainjoin[i] = s1[i];
			i++;
		}
	}
	if (s2)
		chainjoin[i] = s2;
	chainjoin[i + 1] = 0;
	if (s1)
		free(s1);
	return (chainjoin);
}

void	msg_e(char *msg_0, char *token, char *msg_1)
{
	write(2, msg_0, ft_strlen(msg_0));
	write(2, token, ft_strlen(token));
	write(2, msg_1, ft_strlen(msg_1));
}

void	remove_empty_node(t_data_lst *lst_parsing)
{
	t_content	*content;
	t_list		*lst;

	lst = lst_parsing->first;
	while (lst)
	{
		content = (t_content *)lst->content;
		if (!ft_strncmp("", content->word, ft_strlen(content->word) + 1))
			content->to_delete = 1;
		lst = lst->next;
	}
	node_to_del(lst_parsing);
}

void	content_word_tolower(t_data_lst *lst_parsing)
{
	int			u;
	t_content	*content;
	t_list		*lst;

	lst = lst_parsing->first;
	while (lst)
	{
		content = (t_content *)lst->content;
		if (content->type == CMD)
		{
			u = -1;
			while (content->cmd[0][++u])
				content->cmd[0][u] = ft_tolower(content->cmd[0][u]);
		}
		lst = lst->next;
	}
}

// void	print_lst_parsing(t_list *lst_parsing)
// {
// 	t_content	*content;

// 	if (!lst_parsing)
// 		return ;
// 	while (lst_parsing)
// 	{
// 		content = (t_content *)lst_parsing->content;
// 		ft_printf("%s", content->word);
// 		if (content->type == PIPE)
// 			ft_printf("\tPipe");
// 		else if (content->type == OPERATOR)
// 			ft_printf("\tOperator");
// 		else if (content->type == REDIR_O)
// 			ft_printf("\tRedir_O");
// 		else if (content->type == REDIR_I)
// 			ft_printf("\tRedir_I");
// 		else if (content->type == HEREDOC)
// 			ft_printf("\tHeredoc");
// 		else if (content->type == APPEND)
// 			ft_printf("\tAppend");
// 		else if (content->type == CMD)
// 			ft_printf("\tCmd");
// 		else if (content->type == FD)
// 			ft_printf("\tFile");
// 		ft_printf("\tDel %d", content->to_delete);
// 		ft_printf("\tErr %d", content->error);
// 		if (content->type == CMD)
// 		{
// 			ft_printf("\tIn %d", content->infile);
// 			ft_printf("\tOut %d", content->outfile);
// 			ft_printf("\tCod %d", content->exit_code);
// 		}
// 		if (content->type == PIPE)
// 		{
// 			ft_printf("\tIn %d", content->fdp[1]);
// 			ft_printf("\tOut %d", content->fdp[0]);
// 		}
// 		ft_printf("\n");
// 		// ft_print_tab(content->cmd);
// 		lst_parsing = lst_parsing->next;
// 	}
// }
