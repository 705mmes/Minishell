/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:08:45 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/29 15:24:39 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env_index(t_data *big_data, char *find_env)
{
	int		i;
	char	**env;

	(void) env;
	i = 0;
	env = big_data->env;
	while (big_data->env[i])
	{
		if (!ft_strncmp(find_env, big_data->env[i], ft_strlen(find_env)))
			return (i);
		i++;
	}
	return (i);
}

int	ft_array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

char	**rm_tab_index(char **env, int index)
{
	int		i;
	int		u;
	char	**array;

	i = 0;
	u = -1;
	array = malloc(sizeof(char *) * (ft_array_len(env) + 1));
	if (!array)
		return (NULL);
	while (env[i])
	{
		if (i != index)
			array[++u] = env[i];
		i++;
	}
	array[u + 1] = NULL;
	return (array);
}

void	ft_unset(t_content *cont, t_data *big_data)
{
	int		i;
	int		index;
	char	*env;

	i = 0;
	index = 0;
	env = NULL;
	while (cont->cmd[++i])
	{
		index = ft_env_index(big_data, cont->cmd[i]);
		env = ft_getenv(big_data, ft_strdup(cont->cmd[i]));
		if (env != NULL)
			big_data->env = rm_tab_index(big_data->env, index);
	}
}
