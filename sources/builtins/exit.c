/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:18:29 by sammeuss          #+#    #+#             */
/*   Updated: 2023/09/22 17:17:23 by ljerinec         ###   ########.fr       */
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

void	ft_exit_arg(void)
{
	ft_printf("exit\n");
	exit(0);
}

void	ft_exit_args(t_content *content)
{
	ft_printf("exit\n");
	if (is_numeric_arg(content->cmd[1]))
	{
		exit(ft_atoi(content->cmd[1]));
	}
	else
	{
		msg_e("minishell: exit: ", content->cmd[1],
			": numeric argument required");
		exit(255);
	}
}

void	ft_exit_no_arg(t_content *content)
{
	printf("exit\n");
	ft_putstr_fd("minishell: exit: too many arguments", 2);
		content->exit_code = 1;
}

void	ft_exit(t_content *content)
{
	int	nb_args;

	nb_args = ft_arraylen(content->cmd);
	if (nb_args == 1)
		ft_exit_arg();
	else if (nb_args == 2)
		ft_exit_args(content);
	else
		ft_exit_no_arg(content);
}
