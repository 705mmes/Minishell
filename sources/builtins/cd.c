/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:48:53 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/19 00:16:07 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_mini_sig;

void	ft_cd(t_content *content, t_data *big_data)
{
	// char	*pwd;
	char	*path;

	// pwd = NULL;
	path = NULL;
	if (chdir(content->cmd[1]) != -1)
		return ;
	path = check_tilde(content, big_data);
	if (opendir(path) == NULL)
	{
		ft_printf("minishell: cd: %s:", content->cmd[1]);
		perror(" ");
		content->exit_code = 1;
	}
	else
		chdir(path);
}

char	*check_tilde(t_content *content, t_data *big_data)
{
	char	*path;
	char	*pwd;

	pwd = NULL;
	path = NULL;
	if (content->cmd[1] != NULL && ft_strncmp("~", content->cmd[1],
			ft_strlen(content->cmd[1])) == 1)
	{
		pwd = getcwd(pwd, CWD_SIZE);
		path = ft_strjoin(pwd, ft_strdup("/"));
		path = ft_strjoin(path, content->cmd[1]);
	}
	else if (ft_strncmp("~/", content->cmd[1],
			ft_strlen(content->cmd[1])) == 0
		&& ft_strlen(content->cmd[1]) > 2)
				path = ft_strjoin(big_data->root_path,
				&content->cmd[1][1]);
	else if (ft_strncmp("~", content->cmd[1],
			ft_strlen(content->cmd[1])) == 0
		|| ft_strncmp("~/", content->cmd[1],
			ft_strlen(content->cmd[1])) == 0
		|| content->cmd[1] == NULL)
		path = big_data->root_path;
	return (path);
}
