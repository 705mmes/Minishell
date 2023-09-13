/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:27:34 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/13 17:28:09 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_first_egal(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '=')
			return (i);
	return (0);
}

void	ft_export(t_data *big_data, t_content *cont)
{
	int		i;
	int		find_egal;
	char	*env;

	i = 0;
	find_egal = 0;
	env = NULL;
	while (cont->cmd[++i])
	{
		find_egal = find_first_egal(cont->cmd[i]);
		if (find_egal == 0)
			env = ft_getenv(big_data, cont->cmd[i]);
		else
			env = ft_getenv(big_data, ft_substr(cont->cmd[i], 0, find_egal - 1));
		if (env == NULL)
			big_data->env = array_join(big_data->env, cont->cmd[i]);
	}
}
