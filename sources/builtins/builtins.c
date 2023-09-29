/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:58:14 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/29 15:13:01 by ljerinec         ###   ########.fr       */
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
	if (!ft_strncmp("echo", (*cont->cmd), 5)
		|| !ft_strncmp("cd", (*cont->cmd), 3)
		|| !ft_strncmp("pwd", (*cont->cmd), 4)
		|| !ft_strncmp("export", (*cont->cmd), 7)
		|| !ft_strncmp("unset", (*cont->cmd), 6)
		|| !ft_strncmp("env", (*cont->cmd), 4)
		|| !ft_strncmp("exit", (*cont->cmd), 5))
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
		ft_exit(cont);
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

void	poop(t_content *cont, t_data *big_data)
{
	if (!cont->cmd[1])
		ft_export_no_args(big_data, cont);
}
