/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:27:34 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/14 14:48:09 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_env(t_data *big_data, char *find_env)
{
	int		i;

	i = -1;
	if (find_env)
		find_env = ft_strjoin(find_env, "=");
	while (big_data->env[++i])
		if (!ft_strncmp(find_env, big_data->env[i], ft_strlen(find_env)))
			return (1);
	return (0);
}

int	is_export_char(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	else if (c == '_')
		return (1);
	return (0);
}

int	check_export_syntax(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			return (i);
		else if (!is_export_char(str[i]))
		{
			printf("minishell: export: '%c': not a valid identifier\n", str[i]);
			// ft_unset();
			return (-1);
		}
	}
	return (0);
}

void	ft_export(t_data *big_data, t_content *cont)
{
	int		i;
	int		is_syntax;
	int		is_env;

	i = 0;
	is_syntax = 0;
	is_env = 0;
	while (cont->cmd[++i])
	{
		is_syntax = check_export_syntax(cont->cmd[i]);
		if (is_syntax > 0)
			is_env = ft_is_env(big_data, ft_substr(cont->cmd[i], 0, is_syntax - 1));
		if (is_env == 0 && is_syntax > 0)
			big_data->env = array_join(big_data->env, cont->cmd[i]);
	}
}
