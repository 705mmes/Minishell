/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:16:50 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/22 18:58:06 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*create_name(int i, t_data *big_data)
// {
// 	char	*itoa;
// 	char	*name_1;
// 	char	*name_2;

// 	itoa = ft_itoa(i + ft_strlen(big_data->input));
// 	name_1 = ft_strjoin(ft_strdup(".heredoc_"), itoa);
// 	name_2 = ft_strjoin(getcwd(NULL, 0), name_1);
// 	free(name_1);
// 	free(itoa);
// 	return (name_2);
// }

void	sig_heredoc(int sig)
{
	if (sig == SIGINT)
		g_mini_sig = 130;
}

void	ft_newline(void)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	is_heredoc_in_lst(t_list *lst)
{
	t_content	*content;

	while (lst)
	{
		content = (t_content *)lst->content;
		if (content->type == HEREDOC)
			return (1);
		lst = lst->next;
	}
	return (0);
}
