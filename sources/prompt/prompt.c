/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:24:27 by ljerinec          #+#    #+#             */
/*   Updated: 2023/07/17 01:28:27 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(void)
{
	char	*input;

	while (1)
	{
		input = readline("Minishell >> ");
		if (ft_strncmp(input, "", ft_strlen(input)) != 0)
		{
			add_history(input);
			ft_printf(" minishell: %s: command not found\n", input);
		}
		if (!input)
		{
			ft_printf(" exit\n");
			break ;
		}
		free(input);
	}
}

void	signal_changement(void)
{
	struct sigaction	s_sigaction;

	s_sigaction.sa_flags = 0;
	s_sigaction.sa_sigaction = sig_handler;
	sigaction(SIGINT, &s_sigaction, 0);
	sigaction(SIGQUIT, &s_sigaction, 0);
}

void	sig_handler(int sig, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	if (sig == SIGINT)
	{
		write(0, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		rl_redisplay();
}