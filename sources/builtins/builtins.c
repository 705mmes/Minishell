/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:58:14 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/22 15:42:06 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_content *cont)
{
	if (cont->cmd == NULL || (*cont->cmd) == NULL)
		return (0);
	else if (!ft_strncmp("", cont->word, ft_strlen(cont->word) + 1))
	{
		cont->error = 1;
		return (0);
	}
	if (!ft_strncmp("echo", (*cont->cmd), ft_strlen((*cont->cmd) + 1))
		|| !ft_strncmp("cd", (*cont->cmd), ft_strlen((*cont->cmd) + 1))
		|| !ft_strncmp("pwd", (*cont->cmd), ft_strlen((*cont->cmd) + 1))
		|| !ft_strncmp("export", (*cont->cmd), ft_strlen((*cont->cmd) + 1))
		|| !ft_strncmp("unset", (*cont->cmd), ft_strlen((*cont->cmd) + 1))
		|| !ft_strncmp("env", (*cont->cmd), ft_strlen((*cont->cmd) + 1))
		|| !ft_strncmp("exit", (*cont->cmd), ft_strlen((*cont->cmd) + 1)))
		return (1);
	return (0);
}

void	exec_builtins(char *cmd, t_content *cont, t_data *big_data)
{
	if (ft_strncmp(cmd, "pwd", ft_strlen(cmd) + 1) == 0)
		ft_pwd(cont);
	else if (ft_strncmp(cmd, "echo", ft_strlen(cmd) + 1) == 0)
		ft_echo(cont);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		ft_env(big_data, cont);
	else if (ft_strncmp(cmd, "cd", ft_strlen(cmd) + 1) == 0)
		ft_cd(cont, big_data);
	else if (ft_strncmp(cmd, "export", ft_strlen(cmd) + 1) == 0)
		ft_export(big_data, cont);
	else if (ft_strncmp(cmd, "unset", ft_strlen(cmd) + 1) == 0)
		ft_unset(cont, big_data);
	else if (ft_strncmp(cmd, "exit", ft_strlen(cmd) + 1) == 0)
		ft_exit(cont, big_data);
	else
	{
		cont->exit_code = 127;
		msg_e("minishell: ", cont->cmd[0], ": command not found\n");
	}
}

int	is_export_char(char c, int i)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c >= 'a' && c <= 'z')
		return (1);
	else if ((c >= '0' && c <= '9') && i > 0)
		return (1);
	else if (c == '_')
		return (1);
	return (0);
}
