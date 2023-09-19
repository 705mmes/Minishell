/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smunio <smunio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:58:14 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/19 17:14:09 by smunio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_content *cont)
{
	if (!*cont->cmd)
		return (0);
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
		ft_pwd(cont);
	else if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
		ft_echo(cont);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		ft_env(big_data, cont);
	else if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
		ft_cd(cont, big_data);
	else if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
		ft_export(big_data, cont);
	else if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
		ft_unset(cont, big_data);
	else if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
		ft_exit(cont, big_data);
}
