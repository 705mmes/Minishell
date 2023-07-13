/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:24:27 by ljerinec          #+#    #+#             */
/*   Updated: 2023/07/13 17:08:33 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_prompt(void)
{
	char	*line;

	ft_printf("Minishell $ ");
	line = get_next_line(0);
	return (line);
}

void	prompt(void)
{
	char	*line;

	while (1)
	{
		line = new_prompt();
		free(line);
	}
}

void	signal_changement(void)
{
	struct sigaction	s_sigaction;

	s_sigaction.sa_flags = SA_SIGINFO;
	s_sigaction.sa_sigaction = sig_control;
	sigaction(SIGQUIT, &s_sigaction, 0);
	sigaction(SIGINT, &s_sigaction, 0);
}

void	sig_control(int sig, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	if (sig == SIGINT)
		write(0, "\0\n", 2);
	else if (sig == SIGQUIT)
		exit(1);
}
