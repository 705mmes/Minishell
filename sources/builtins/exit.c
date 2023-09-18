/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:18:29 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/17 17:11:07 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9')
			|| str[i] == '-' || str[i] == '+')
			i++;
		else
			return (0);
	}
	return (1);
}

void	ft_exit(t_content *content, t_data *big_data)
{
	int	nb_args;

	(void)big_data;
	nb_args = ft_arraylen(content->cmd);
	if (nb_args == 1)
	{
		ft_printf("exit\n");
		exit(1);
	}
	else if (nb_args == 2)
	{
		ft_printf("exit\n");
		if (is_numeric_arg(content->cmd[1]))
			exit(ft_atoi(content->cmd[1]));
		else
		{
			write(2, "minishell: exit: ", ft_strlen("minishell: exit: "));
			write(2, content->cmd[1], ft_strlen(content->cmd[1]));
			ft_putstr_fd(": numeric argument required", 2);
			exit(255);
		}
	}
	else
	{
		printf("exit\n");
		ft_putstr_fd("minishell: exit: too many arguments", 2);
		content->exit_code = 1;
	}
}
