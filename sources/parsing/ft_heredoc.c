/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:13:52 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/22 19:03:24 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_mini_sig;

int	is_not_delimitor_after_heredoc(t_list *lst)
{
	t_content	*content;

	while (lst)
	{
		content = ((t_content *)lst->content);
		if (content->type == HEREDOC)
		{
			if (lst->next == NULL)
			{
				printf("minishell: syntax error ");
				printf("near unexpected token 'newline'\n");
				g_mini_sig = 2;
				return (1);
			}
			else if (((t_content *)lst->next->content)->type != FD)
			{
				printf("minishell: syntax error near unexpected token %s\n",
					((t_content *)lst->next->content)->word);
				g_mini_sig = 2;
				return (1);
			}
		}
		lst = lst->next;
	}
	return (0);
}

void	read_on_heredoc(t_content *c_next, int fd)
{
	char	*input;

	signal(SIGINT, sig_heredoc);
	while (1)
	{
		input = readline("> ");
		if (g_mini_sig == 130)
			exit(1);
		else if ((input && !ft_strncmp(input, "\n", ft_strlen(input))))
			ft_newline();
		else if ((input && !ft_strncmp(input, "", ft_strlen(input)))
			|| input == NULL)
			exit(1);
		else if (!ft_strncmp(c_next->word, input, ft_strlen(input)))
			break ;
		else
			write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
	exit(0);
}

void	heredoc_read(t_list *lst)
{
	t_content	*c_next;
	int			fd[2];
	pid_t		forked;
	int			exit_code;

	c_next = (t_content *)lst->next->content;
	pipe(fd);
	forked = fork();
	if (forked == 0)
		read_on_heredoc(c_next, fd[1]);
	else
		waitpid(forked, &exit_code, 0);
	ft_signal();
	if (fd[1] && !WEXITSTATUS(exit_code))
		heredoc_sucess(&c_next, fd);
	else
		heredoc_failed(fd, &c_next);
}

void	do_heredoc_things(t_list *lst)
{
	t_content	*content;
	t_content	*content_next;
	int			i;

	i = 0;
	while (lst)
	{
		if (!lst->next)
			return ;
		content = (t_content *)lst->content;
		content_next = (t_content *)lst->next->content;
		if (content->type == HEREDOC && content_next->type == FD)
			heredoc_read(lst);
		lst = lst->next;
	}
}

void	heredoc_gestion(t_data *big_data)
{
	t_list	*lst;

	lst = big_data->lst_parsing->first;
	if (!is_heredoc_in_lst(lst))
		return ;
	do_heredoc_things(lst);
}
