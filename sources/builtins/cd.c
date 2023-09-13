/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:48:53 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/13 15:11:17 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_content *content)
{
	char	*path;

	if (content->cmd[1] != NULL)
		path = content->cmd[1];
	if (access(path, F_OK) == -1)
		perror("Bad file access");
	else
		chdir(path);
}
