/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:58:14 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/13 16:55:29 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_content *cont)
{
	// if (!cont->cmd && !(*cont->cmd))
	// 	return (2);
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

void	exec_builtins(char *cmd, t_content *cont, t_data *big_data)
{
	if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
		ft_pwd();
	else if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
		ft_echo(cont);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		ft_env(big_data);
	else if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
		ft_cd(cont);
}
