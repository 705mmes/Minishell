/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:27:34 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/22 18:17:32 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_mini_sig;

int	ft_is_env(t_data *big_data, char *find_env)
{
	int		i;

	i = -1;
	if (find_env)
		find_env = ft_strjoin(find_env, ft_strdup("="));
	while (big_data->env[++i])
		if (!ft_strncmp(find_env, big_data->env[i], ft_strlen(find_env)))
			return (1);
	return (0);
}

int	check_export_syntax(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=' && i > 0)
			return (i);
		else if (!is_export_char(str[i], i))
		{
			ft_printf("minishell: export: `%s':", str);
			ft_putstr_fd(" not a valid identifier", 2);
			return (-1);
		}
	}
	return (0);
}

void	normed(int *is_syntax, t_content *cont, int i)
{
	*is_syntax = check_export_syntax(cont->cmd[i]);
	if (*is_syntax < 0)
		cont->exit_code = 1;
}

void	ft_export(t_data *big_data, t_content *cont)
{
	int		i;
	int		is_syntax;
	int		is_env;

	i = 0;
	is_syntax = 0;
	is_env = 0;
	if (cont->outfile != 1)
		return (cont->exit_code = 1, (void)0);
	if (!cont->cmd[1])
		ft_export_no_args(big_data, cont);
	while (cont->cmd[++i])
	{
		normed(&is_syntax, cont, i);
		if (is_syntax > 0)
		{
			is_env = ft_is_env(big_data,
					ft_substr(cont->cmd[i], 0, is_syntax - 1));
			if (is_env == 0 && !ft_env_exist(big_data, cont->cmd[i]))
			{
				big_data->env = array_join(big_data->env,
						ft_strdup(cont->cmd[i]));
				cont->exit_code = 0;
			}
		}
	}
}

int	ft_env_exist(t_data *big_data, char *env)
{
	int	i;
	int	len;

	len = 0;
	i = -1;
	while (big_data->env[++i])
	{
		while (big_data->env[i][len] != '=')
			len++;
		if (!ft_strncmp(env, big_data->env[i], len))
		{
			free(big_data->env[i]);
			big_data->env[i] = ft_strdup(env);
			return (1);
		}
		len = 0;
	}
	return (0);
}
