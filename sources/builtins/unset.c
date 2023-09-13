/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:08:45 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/13 18:06:09 by sammeuss         ###   ########.fr       */
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
		if (ft_strncmp(find_env, big_data->env[i], ft_strlen(find_env)))
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

char	**rm_tab_index(t_data *big_data, int index)
{
	int		i;
	char	**array;

	i = -1;
	ft_print_tab(big_data->env);
	array = malloc(sizeof(char *) * (ft_array_len(big_data->env) - 1));
	while (++i < index)
		array[i] = big_data->env[i];
	free(big_data->env[i]);
	ft_print_tab(array);
	i++;
	while (big_data->env[++i])
		array[i - 1] = big_data->env[i];
	array[i] = NULL;
	free(big_data->env);
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
		env = ft_getenv(big_data, cont->cmd[i]);
		if (env != NULL)
			big_data->env = rm_tab_index(big_data, index);
		ft_print_tab(big_data->env);
	}
}

// void	ft_unset(t_content *content, t_data *big_data)
// {
// 	char	*arg;

// 	if (!content->cmd[1])
// 		return ;
// 	arg = ft_getenv(big_data, content->cmd[1]);
// 	if (arg == NULL)
// 		return ;
// 	big_data->env = rm_tab_index(big_data, content);
// }
