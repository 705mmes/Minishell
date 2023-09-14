/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:24:32 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/14 00:51:18 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_content *cont)
{
	char	buffer[CWD_SIZE];

	if (getcwd(buffer, CWD_SIZE) == NULL)
		perror("Getcwd failed");
	else
	{
		write(cont->outfile, buffer, ft_strlen(buffer));
		write(cont->outfile, "\n", 1);
	}
}
