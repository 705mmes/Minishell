/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smunio <smunio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:24:27 by ljerinec          #+#    #+#             */
/*   Updated: 2023/09/18 19:15:36 by smunio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_mini_sig;

void	ft_signal_in_fork(void)
{
	struct sigaction	s_sigaction;

	s_sigaction.sa_flags = 0;
	s_sigaction.sa_sigaction = sig_handler_in_fork;
	sigaction(SIGINT, &s_sigaction, 0);
	sigaction(SIGQUIT, &s_sigaction, 0);
}

void	ft_signal(void)
{
	struct sigaction	s_sigaction;

	s_sigaction.sa_flags = 0;
	s_sigaction.sa_sigaction = sig_handler;
	sigaction(SIGINT, &s_sigaction, 0);
	sigaction(SIGQUIT, &s_sigaction, 0);
}

void	sig_handler_in_fork(int sig, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	if (sig == SIGINT)
		ft_printf("\n");
	else if (sig == SIGQUIT)
		ft_printf("");
}

void	sig_handler(int sig, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	if (sig == SIGINT)
	{
		g_mini_sig += SIGINT;
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		rl_redisplay();
}

int	is_ctrl_d(t_data *big_data, char *input)
{
	if (input == NULL)
	{
		ft_printf("exit\n");
		big_data->input = NULL;
		ft_signal_in_fork();
		return (TRUE);
	}
	return (FALSE);
}
