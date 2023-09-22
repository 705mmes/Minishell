/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:58:14 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/22 14:54:41 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_strncmp_spe(const char *s1, const char *s2)
// {
// 	size_t	i;
// 	size_t	n;

// 	i = 0;
// 	if (ft_strlen(s1) > ft_strlen(s2))
// 		n = ft_strlen(s1);
// 	else
// 		n = ft_strlen(s2);
// 	while (i < n && (s1[i] || s2[i]))
// 	{
// 		if (s1[i] != s2[i])
// 			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// 		i++;
// 	}
// 	return (0);
// }

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
