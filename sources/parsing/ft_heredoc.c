/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:13:52 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/20 15:44:30 by ljerinec         ###   ########.fr       */
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
	{
		g_mini_sig = 130;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	heredoc_read(t_list *lst, int i, t_data *big_data)
{
	t_content	*c_next;
	char		*input;
	char		*file_name;
	int			fd;

	c_next = (t_content *)lst->next->content;
	file_name = create_name(i);
	fd = open(file_name, O_CREAT | O_APPEND
			| O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	input = NULL;
	while (g_mini_sig != 130)
	{
		input = readline("> ");
		printf("%d\n", g_mini_sig);
		if ((input && !ft_strncmp(input, "\n", ft_strlen(input))))
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		else if ((input && !ft_strncmp(input, "", ft_strlen(input))))
		{
			close(fd);
			unlink(file_name);
			free(file_name);
			file_name = NULL;
		}
		else if (!ft_strncmp(c_next->word, input, ft_strlen(input)))
			break ;
		else if (g_mini_sig == 130)
			break ;
		else
			write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		input = NULL;
		free(input);
	}
	ft_signal();
	if (fd)
	{
		c_next->word = file_name;
		big_data->heredocs = array_join(big_data->heredocs, file_name);
	}
	close(fd);
}

void	do_heredoc_things(t_list *lst, t_data *big_data)
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
			heredoc_read(lst, i++, big_data);
		lst = lst->next;
	}
}

void	heredoc_gestion(t_data *big_data)
{
	t_list	*lst;

	lst = big_data->lst_parsing->first;
	if (!is_heredoc_in_lst(lst))
		return ;
	do_heredoc_things(lst, big_data);
}
