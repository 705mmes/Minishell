/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:58:14 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/13 14:14:24 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_content *cont)
{
	if (!cont->cmd && !(*cont->cmd))
		return (2);
	if (ft_strncmp("echo", (*cont->cmd), ft_strlen((*cont->cmd))) == 0
		|| ft_strncmp("cd", (*cont->cmd), ft_strlen((*cont->cmd))) == 0
		|| ft_strncmp("pwd", (*cont->cmd), ft_strlen((*cont->cmd))) == 0
		|| ft_strncmp("export", (*cont->cmd), ft_strlen((*cont->cmd))) == 0
		|| ft_strncmp("unset", (*cont->cmd), ft_strlen((*cont->cmd))) == 0
		|| ft_strncmp("env", (*cont->cmd), ft_strlen((*cont->cmd))) == 0
		|| ft_strncmp("exit", (*cont->cmd), ft_strlen((*cont->cmd))) == 0)
		return (1);
	return (0);
}

void	exec_builtins(char *cmd, t_content *cont)
{
	if (ft_strncmp(cmd, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(cmd, "echo", 4) == 0)
		ft_echo(cont);

}
