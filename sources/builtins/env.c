/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:04:10 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/23 15:10:19 by ljerinec         ###   ########.fr       */
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
	int	u;

	u = -1;
	i = -1;
	while (env[++i])
	{	
		write(cont->outfile, "declare -x ", 11);
		while (env[i][++u])
		{
			if (env[i][u] == '=')
			{
				write(cont->outfile, &env[i][u], 1);
				write(cont->outfile, "\"", 1);
				u++;
			}
			write(cont->outfile, &env[i][u], 1);
		}
		write(cont->outfile, "\"", 1);
		write(cont->outfile, "\n", 1);
		u = -1;
	}
	ft_free_array(env);
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

	i = -1;
	u = -1;
	tmp = NULL;
	new = array_dup(env);
	while (new[++i])
	{
		while (new[++u])
		{
			if (new[u + 1] && new[u]
				&& ft_strncmp(new[u], new[u + 1], ft_strlen(new[u]) + 1) > 0)
			{
				tmp = new[u];
				new[u] = new[u + 1];
				new[u + 1] = tmp;
			}
		}
		u = -1;
	}
	return (new);
}
