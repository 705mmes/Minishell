/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:08:45 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/13 16:56:08 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env_index(t_data *big_data, char *find_env)
{
	int		i;
	char	**env;

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

void	unset(t_content *content, t_data *big_data)
{
	char	*arg;
	int		i;

	if (!content->cmd[1])
		return ;
	arg = ft_getenv(big_data, content->cmd[1]);
	i = ft_env_index(big_data, content->cmd[1]);
	if (arg == NULL)
		return ;
}

