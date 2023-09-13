/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:08:45 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/13 17:32:53 by sammeuss         ###   ########.fr       */
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

// char	**rm_tab_index(t_data *big_data, t_content *content)
// {
// 	int		i;
// 	char	*r;
// 	char	*array;

// 	i = -1;
// 	array = big_data->env;
// 	r = malloc(sizeof(char *) * (ft_array_len(array) - 1));
// 	while (++i < ft_env_index(big_data, content->cmd[1]))
// 		array[i] = big_data->env[i];
// }

// void	unset(t_content *content, t_data *big_data)
// {
// 	char	*arg;
// 	int		i;

// 	(void) i;
// 	if (!content->cmd[1])
// 		return ;
// 	arg = ft_getenv(big_data, content->cmd[1]);
// 	i = ft_env_index(big_data, content->cmd[1]);
// 	if (arg == NULL)
// 		return ;
// }

