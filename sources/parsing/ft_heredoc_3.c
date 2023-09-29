/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:20:50 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/29 16:37:33 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_failed(int *fd, t_content **c_next)
{
	(*c_next)->error = 1;
	close(fd[0]);
	close(fd[1]);
}

void	heredoc_sucess(t_content **c_next, int *fd)
{
	(*c_next)->infile = fd[0];
	close(fd[1]);
}
