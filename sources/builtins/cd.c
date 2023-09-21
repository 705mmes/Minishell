/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:48:53 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/21 13:25:11 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_mini_sig;

void	ft_cd(t_content *cont, t_data *big_data)
{
	char	*pwd;
	char	*path;

	pwd = NULL;
	path = NULL;
	if (chdir(cont->cmd[1]) != -1)
		return ;
	if (cont->cmd[1] != NULL)
		path = check_tilde(cont, big_data, pwd, path);
	else
		path = big_data->root_path;
	if (opendir(path) == NULL)
	{
		ft_printf("minishell: cd: %s", cont->cmd[1]);
		perror(" ");
		cont->exit_code = 1;
	}
	else
		chdir(path);
}

char	*check_tilde(t_content *cont, t_data *big, char *pwd, char *path)
{
	if (!ft_strncmp("~", cont->cmd[1], 1))
	{
		path = ft_strjoin(path, big->root_path);
		cont->cmd[1]++;
		if (!ft_strncmp("/", cont->cmd[1], 1))
		{
			cont->cmd[1]++;
			if (cont->cmd[1][0] != 0)
			{
				path = ft_strjoin(path, ft_strdup("/"));
				path = ft_strjoin(path, cont->cmd[1]);
			}
		}
		else if (cont->cmd[1][0] != 0)
			return (NULL);
	}
	else
	{
		pwd = getcwd(pwd, CWD_SIZE);
		path = ft_strjoin(pwd, ft_strdup("/"));
		path = ft_strjoin(path, cont->cmd[1]);
	}
	return (path);
}
