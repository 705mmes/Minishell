/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:22:43 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/06 18:12:34 by sammeuss         ###   ########.fr       */
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

void	print_lst_parsing(t_list *lst_parsing)
{
	t_content	*content;

	if (!lst_parsing)
		return ;
	while (lst_parsing)
	{
		content = (t_content *)lst_parsing->content;
		ft_printf("%s", content->word);
		if (content->type == PIPE)
			ft_printf("\tPipe");
		else if (content->type == OPERATOR)
			ft_printf("\tOperator");
		else if (content->type == REDIR_O)
			ft_printf("\tRedir_O");
		else if (content->type == REDIR_I)
			ft_printf("\tRedir_I");
		else if (content->type == HEREDOC)
			ft_printf("\tHeredoc");
		else if (content->type == APPEND)
			ft_printf("\tAppend");
		else if (content->type == CMD)
			ft_printf("\tCmd");
		else if (content->type == FD)
			ft_printf("\tFile");
		ft_printf("\t%d", content->to_delete);
		if (content->type == CMD)
		{
			ft_printf("\tIn %d", content->infile);
			ft_printf("\tOut %d", content->outfile);
		}
		else if (content->type == PIPE)
		{
			ft_printf("\tIn %d", content->fdp[0]);
			ft_printf("\tOut %d", content->fdp[1]);
		}
			// ft_print_tab(content->cmd);
		ft_printf("\n");
		lst_parsing = lst_parsing->next;
	}
}