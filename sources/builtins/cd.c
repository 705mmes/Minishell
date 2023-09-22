/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:48:53 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/22 14:08:40 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_mini_sig;

// void	set_oldpwd(t_data *big_data)
// {
	
// }

// void	set_pwd(t_data *big_data, char *path)
// {
	
// }

int	arg_good(t_content *cont, t_data *big_data)
{
	// char	*oldpwd;
	(void)big_data;

	// oldpwd = ft_getenv(big_data, ft_strdup("PWD"));
	if (cont->cmd && cont->cmd[1])
	{
		if (chdir(cont->cmd[1]) != -1)
		{
			// set_oldpwd();
			// set_pwd();
			return (1);
		}
		else
			return (0);
	}
	return (0);
}

void	ft_cd(t_content *cont, t_data *big_data)
{
	char	*pwd;
	char	*path;

	pwd = NULL;
	path = NULL;
	if (arg_good(cont, big_data))
		return ;
	if (cont->cmd[1] != NULL)
		path = check_tilde(cont, big_data, pwd, path);
	else if (big_data->root_path)
		path = big_data->root_path;
	else
		return (msg_e("minishell: ", cont->word, ": HOME not set\n"), (void)0);
	if (opendir(path) == NULL)
	{
		ft_printf("minishell: cd: %s", cont->cmd[1]);
		perror(" ");
		cont->exit_code = 1;
	}
	else
	{
		// set_oldpwd();
		chdir(path);
		// set_pwd();
	}
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
		pwd = getcwd(NULL, 0);
		path = ft_strjoin(pwd, ft_strdup("/"));
		path = ft_strjoin(path, cont->cmd[1]);
	}
	return (path);
}
