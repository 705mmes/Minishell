/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:24:27 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/22 17:16:04 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_mini_sig;

void	ft_signal_in_fork(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_signal(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_mini_sig = 130;
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}	
}

int	is_ctrl_d(t_data *big_data, char *input)
{
	if (input == NULL)
	{
		ft_printf("exit\n");
		big_data->input = NULL;
		return (TRUE);
	}
	return (FALSE);
}
