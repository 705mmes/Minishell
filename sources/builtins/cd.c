/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smunio <smunio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:48:53 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/19 14:43:53 by smunio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_mini_sig;

void	ft_cd(t_content *content, t_data *big_data)
{
	char	*pwd;
	char	*path;

	pwd = NULL;
	path = NULL;
	if (chdir(content->cmd[1]) != -1)
		return ;
	if (content->cmd[1] != NULL)
		path = check_tilde(content, big_data, pwd);
	else
		path = big_data->root_path;
	if (opendir(path) == NULL)
	{
		ft_printf("minishell: cd: %s:", content->cmd[1]);
		perror(" ");
		content->exit_code = 1;
	}
	else
		chdir(path);
}

char	*check_tilde(t_content *content, t_data *big_data, char *pwd)
{
	char	*path;

	path = NULL;
	if (!ft_strncmp("~", content->cmd[1], 1))
	{
		path = ft_strjoin(path, big_data->root_path);
		content->cmd[1]++;
		if (!ft_strncmp("/", content->cmd[1], 1))
		{
			content->cmd[1]++;
			if (content->cmd[1][0] != 0)
			{
				path = ft_strjoin(path, ft_strdup("/"));
				path = ft_strjoin(path, content->cmd[1]);
			}
		}
	}
	else
	{
		pwd = getcwd(pwd, CWD_SIZE);
		path = ft_strjoin(pwd, ft_strdup("/"));
		path = ft_strjoin(path, content->cmd[1]);
	}
	return (path);
}
