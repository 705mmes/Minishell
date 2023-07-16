/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:38:49 by ljerinec          #+#    #+#             */
/*   Updated: 2023/07/16 23:24:21 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	signal_changement();
	prompt();
	ft_printf(" exit\n");
	return (0);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <signal.h>
// #include <readline/readline.h>
// #include <readline/history.h>

// void	handle_signal(int signo) {
// 	if (signo == SIGINT)
// 	{
// 		rl_on_new_line();
// 		// rl_redisplay();
// 	}
// 	else if (signo == SIGQUIT)
// 		return ;
// }

// int main() {
//     // Configuration des signaux pour CTRL-C et CTRL-
// 	signal(SIGINT, handle_signal);
// 	signal(SIGQUIT, handle_signal);

// 	char* input;

// 	while ((input = readline("Minishell $ ")) != NULL) {
// 		if (strcmp(input, "") != 0)
// 			add_history(input);
// 		free(input);
//     }
//     printf("exit\n");
//     return 0;
// }

