/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:24:27 by ljerinec          #+#    #+#             */
/*   Updated: 2023/07/13 16:42:53 by ljerinec         ###   ########.fr       */
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

	line = new_prompt();
	if (line[0] == '\n' || line[0] == '\0')
	{
		free(line);
		line = new_prompt();
	}
	else if (line)
	{
		write(0, "\0", 1);
		printf(" minishell: command not found: %s", line);
		free(line);
		line = new_prompt();
	}
	else
		free(line);
}

void	signal_changement(void)
{
	struct sigaction	s_sigaction;

	s_sigaction.sa_sigaction = sig_control;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGQUIT, &s_sigaction, 0);
	sigaction(SIGINT, &s_sigaction, 0);
}

void	sig_control(int sig, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	if (sig == SIGINT)
		write(0, "\0", 1);
	else if (sig == SIGQUIT)
		write(0, "\0", 1);
}
