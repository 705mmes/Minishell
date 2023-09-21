/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:16:50 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/21 13:21:31 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*get_address(void)
{
	int	*rnd;

	rnd = malloc(sizeof(int *) * 1);
	return (rnd);
}

char	*create_name(int i)
{
	char	*itoa;
	char	*name;
	int		*rnd;

	rnd = get_address();
	if (*rnd < 0)
		*rnd *= -1;
	itoa = ft_itoa(i + (*rnd));
	free(rnd);
	name = ft_strjoin(ft_strdup(".heredoc_"), itoa);
	free(itoa);
	return (name);
}

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
