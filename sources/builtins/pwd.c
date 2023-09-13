/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:24:32 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/13 16:57:01 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	buffer[CWD_SIZE];

	if (getcwd(buffer, CWD_SIZE) == NULL)
		perror("Getcwd failed");
	else
	{
		write(1, buffer, ft_strlen(buffer));
		write(1, "\n", 1);
	}
}
