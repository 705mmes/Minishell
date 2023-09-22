/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:20:50 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/22 17:51:53 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_failed(char *file, int fd, t_content **c_next)
{
	free((*c_next)->word);
	(*c_next)->word = file;
	(*c_next)->error = 1;
	if (fd > 0)
		close(fd);
	unlink(file);
	rl_replace_line("", 0);
	rl_redisplay();
}

void	heredoc_sucess(t_content **c_next, char *file, t_data *big, int fd)
{
	free((*c_next)->word);
	(*c_next)->word = file;
	big->heredocs = array_join(big->heredocs, ft_strdup(file));
	close(fd);
}
