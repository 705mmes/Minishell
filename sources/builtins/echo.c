/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:38:35 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/13 13:49:38 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_content *content)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	if (!content->cmd[1])
		return ((void)printf("no args\n"));
	else if (ft_strncmp(content->cmd[1], "-n", 2) == 0)
	{
		flag = 1;
		i++;
	}
	while (content->cmd[++i])
	{
		write(content->outfile, content->cmd[i], ft_strlen(content->cmd[i]));
		write(content->outfile, " ", 1);
	}
	if (flag == 0)
		write(content->outfile, "\n", 1);
}
