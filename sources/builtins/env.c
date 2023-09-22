/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:04:10 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/22 14:02:47 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_data *big_data, t_content *cont)
{
	int	i;

	i = -1;
	if (!big_data->env && !(*big_data->env))
		return ;
	while (big_data->env[++i])
		ft_putstr_fd(big_data->env[i], cont->outfile);
}

void	ft_env_no_args(char **env, t_content *cont)
{
	int	i;

	i = -1;
	while (env[++i])
	{	
		write(cont->outfile, "declare -x ", 11);
		ft_putstr_fd(env[i], cont->outfile);
	}
}

void	ft_export_no_args(t_data *big_data, t_content *cont)
{
	char	**new;

	new = NULL;
	if (!big_data->env && !(*big_data->env))
		return ;
	new = ft_sort_env(big_data->env, new);
	ft_env_no_args(new, cont);
}

char	**ft_sort_env(char **env, char **new)
{
	int		i;
	int		u;
	char	*tmp;

	i = 0;
	u = 0;
	tmp = NULL;
	new = array_dup(env);
	while (new[i])
	{
		while (new[u])
		{
			if (new[u + 1] && new[u]
				&& ft_strncmp(new[u], new[u + 1], ft_strlen(new[u]) + 1) > 0)
			{
				// printf("swaping :%s & %s\n", );
				tmp = new[u];
				new[u] = new[u + 1];
				new[u + 1] = tmp;
			}
			u++;
		}
		u = 0;
		i++;
	}
	return (new);
}
